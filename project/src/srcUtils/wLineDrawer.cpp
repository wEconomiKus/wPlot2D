/**
 * @file wLineDrawer.cpp
 * @brief Implementation of the LineDrawer class.
 */

#include "wLineDrawer.hpp"
#include <cmath>
#include <numbers>

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public static methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

float LineDrawer::drawLine( sf::RenderWindow& window, const sf::Vector2f& point1, const sf::Vector2f& point2,
	const sf::Color& color, float thickness, LineStyleComponent::LineStyle style, float dashLength,
	float gapLength, float patternOffset )
{
	// Early exit: nothing to draw if both points are identical
	if (point1 == point2)
	{
		return patternOffset; // keep offset unchanged
	}

	// Compute direction vector and its normalized form
	sf::Vector2f dir = point2 - point1;
	float length = dir.length( );
	sf::Vector2f unitDir = dir.normalized( );

	// Perpendicular vector scaled by half the thickness -> used to build quads
	sf::Vector2f offset = unitDir.perpendicular( ) * ( thickness / 2.0f );

	// Case 1: Solid line -> draw the full quad once
	if (style == LineStyleComponent::LineStyle::Solid)
	{
		// Simple rectangle strip for the full segment
		sf::VertexArray quad( sf::PrimitiveType::TriangleStrip, 4) ;

		quad[ 0 ] = sf::Vertex( point1 - offset, color );
		quad[ 1 ] = sf::Vertex( point1 + offset, color );
		quad[ 2 ] = sf::Vertex( point2 - offset, color );
		quad[ 3 ] = sf::Vertex( point2 + offset, color );

		window.draw( quad );

		return patternOffset; // no change, pattern not used
	}

	// Case 2: Dashed or Dotted
	/*
		Pattern length depends on the style:
		- dashed : dashLength + gapLength
		- dotted : thickness (dot size) + gapLength
	*/
	float patternLength = (style == LineStyleComponent::LineStyle::Dashed)
		? (dashLength + gapLength)
		: (thickness + gapLength);

	float traveled = 0.0f; // distance already covered along the segment

	while (traveled < length)
	{
		// Position inside the current pattern cycle (using global offset)
		float localPos = fmod( patternOffset + traveled, patternLength );

		// How much of the current dash/dot is left to draw
		float segmentLength = 0.0f;
		if (style == LineStyleComponent::LineStyle::Dashed)
		{
			segmentLength = dashLength - localPos;
		}
		else // dotted
		{
			segmentLength = thickness - localPos;
		}
		
		// If segmentLength <= 0 -> we are in a gap, skip to the next cycle
		if (segmentLength <= 0.0f)
		{
			float skip = patternLength - localPos; // jump to start of next cycle
			traveled += skip;
			continue;
		}

		// Clamp the segment so we don’t go beyond the end of the line
		float segStart = traveled;
		float segEnd = std::min( traveled + segmentLength, length );

		// Compute segment endpoints in world coordinates
		sf::Vector2f p1 = point1 + unitDir * segStart;
		sf::Vector2f p2 = point1 + unitDir * segEnd;

		// Draw this dash/dot as a quad (thick line segment)
		sf::VertexArray quad( sf::PrimitiveType::TriangleStrip, 4 );
		quad[ 0 ] = sf::Vertex( p1 - offset, color );
		quad[ 1 ] = sf::Vertex( p1 + offset, color );
		quad[ 2 ] = sf::Vertex( p2 - offset, color );
		quad[ 3 ] = sf::Vertex( p2 + offset, color );
		window.draw( quad );

		// Advance to the end of this drawn segment
		traveled = segEnd;
	}

	// Update and return the pattern offset so the next call starts aligned
	return fmod( patternOffset + length, patternLength );
}

void LineDrawer::drawPolylineRound( sf::RenderWindow& window, const std::vector< sf::Vector2f >& points, const sf::Color& color, float thickness,
	LineStyleComponent::LineStyle style, float dashLength, float gapLength, unsigned int arcResolution )
{
	// Early exit: a polyline requires at least two points
	if (points.size( ) < 2)
	{
		return;
	}

	// Keeps track of the current offset inside the dash/dot pattern so the pattern stays continuous across all connected segments.
	float patternOffset = 0.0f;

	// Iterate over consecutive pairs of points
	for (size_t i = 0; i < points.size( ) - 1; ++i)
	{
		sf::Vector2f p1 = points[ i ];
		sf::Vector2f p2 = points[ i+1 ];

		// Ignore degenerate segments (zero length)
		if (p1 == p2)
		{
			continue;
		}

		// --- Step 1: Draw the current segment ---
		// Calls drawLine( ), which handles solid/dashed/dotted rendering.
		// drawLine( ) returns the updated pattern offset, so the dash/dot
		// pattern continues seamlessly into the next segment.
		patternOffset = drawLine( window, p1, p2, color, thickness, style, dashLength, gapLength, patternOffset );

		// --- Step 2: Draw a round join (only for SOLID style) ---
		// For dashed/dotted, round joins would look strange, so we skip them.
		if (style == LineStyleComponent::LineStyle::Solid && i < points.size( ) - 2)
		{
			sf::Vector2f p3 = points[ i+2 ];

			// Skip degenerate next segment
			if (p2 == p3)
			{
				continue;
			}
			
			// Compute normalized direction vectors of the two segments:
			// dir1 = direction of [p1 -> p2]
			// dir2 = direction of [p2 -> p3]
			sf::Vector2f dir1 = (p2 - p1).normalized( );
			sf::Vector2f dir2 = (p3 - p2).normalized( );

			// Compute normals (perpendiculars) of the two directions
			sf::Vector2f n1( -dir1.y, dir1.x );
			sf::Vector2f n2( -dir2.y, dir2.x );

			// Convert normals to angles (in radians)
			float angle1 = std::atan2( n1.y, n1.x );
			float angle2 = std::atan2( n2.y, n2.x );

			// Ensure angles are in the correct order (no wrap-around issue)
			if (angle2 < angle1)
			{
				angle2 += 2.0f * static_cast< float >( std::numbers::pi );
			}

			// Subdivide the arc between n1 and n2 into 'arcResolution' steps
			float step = (angle2 - angle1) / static_cast< float >( arcResolution );

			// Build the round join as a triangle fan centered on p2
			sf::VertexArray arc( sf::PrimitiveType::Triangles );
			for (unsigned int k = 0; k < arcResolution; ++k)
			{
				float a1 = angle1 + k * step;
				float a2 = angle1 + (k + 1) * step;

				// Unit vectors along the arc
				sf::Vector2f v1( std::cos( a1 ), std::sin( a1 ) );
				sf::Vector2f v2( std::cos( a2 ), std::sin( a2 ) );

				// Triangle = (center, arc point 1, arc point 2)
				arc.append( sf::Vertex( p2, color ) );
				arc.append( sf::Vertex( p2 + v1 * (thickness / 2.0f), color ) );
				arc.append( sf::Vertex( p2 + v2 * (thickness / 2.0f), color ) );
			}

			// Render the arc
			window.draw( arc );
		}
	}
}

}//End of namespace wEngine