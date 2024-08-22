
#include <cmath>

#include "math.h"

using std::vector;


vector<pixel> compute_line(pixel start_px, pixel end_px) //it is assumed these are valid pixels i.e. not out of bounds
{
	vector<pixel> out;
	
	if (start_px == end_px)
	{
		out.push_back(start_px);
		return out; 
	}

	pixel delta = end_px - start_px; //by previous check, delta != 0 vector

	if (delta.x == 0) //vertical line
	{
		int y_mag = std::abs(delta.y); 
		delta = delta / y_mag; //y_mag can not be 0 since delta is not uniformly 0

		pixel current = start_px;

		out.push_back(start_px);

		while(current != end_px) //head in a straight vertical line to end_px
		{
			current += delta;
			out.push_back(current);
		}

		return out;

	}

	if (delta.y == 0) //horizontal line
	{
		int x_mag = std::abs(delta.x);
		delta = delta / x_mag;

		pixel current = start_px;

		out.push_back(start_px);

		while (current != end_px)
		{
			current += delta;
			out.push_back(current);
		}

		return out;
	}

	//both components are nonzero; delta is unchanged, out is empty - currently 4 cases here - maybe could reduce that - lines are currently too thick -> can probably fix that too

	float slope = static_cast<float>(delta.y) / static_cast<float>(delta.x); 

	if (delta.x > 0 && slope > 0) //x and y both increase
	{
		int current_y = start_px.y;

		for (int i = 0; i <= delta.x; i++) 
		{
			int current_x = start_px.x + i; //we're currently filling in the line at this x value

			int goal_y = std::min(static_cast<int>(std::round(start_px.y + slope * i)), end_px.y); //what y value are we going to reach in this 1-pixel wide zone?

			for (int j = current_y; j <= goal_y; j++) //fill in all y's between current and goal
			{
				out.push_back({ current_x, j });
			}

			double integral_part;
			double fractional = modf(start_px.y + slope * i, &integral_part);

			current_y = goal_y;
			
		}
	}

	
	if (delta.x > 0 && slope < 0) //x increasing, y decreasing
	{
		int current_y = start_px.y;

		for (int i = 0; i <= delta.x; i++)
		{
			int current_x = start_px.x + i; //we're currently filling in the line at this x value

			int goal_y = std::max(static_cast<int>(std::round(start_px.y + slope * i)), end_px.y); //what y value are we going to reach in this 1-pixel wide zone?

			for (int j = current_y; j >= goal_y; j--)
			{
				out.push_back({ current_x,j });				
			}

			current_y = goal_y - 1;
		}
	}

	if (delta.x < 0 && slope > 0) //x decreasing, y decreasing
	{
		int current_y = start_px.y;

		for (int i = 0; i >= delta.x; i--)
		{
			int current_x = start_px.x + i; //we're currently filling in the line at this x value

			int goal_y = std::max(static_cast<int>(std::round(start_px.y + slope * i)), end_px.y);

			for (int j = current_y; j >= goal_y; j--)
			{
				out.push_back({ current_x, j });			
			}

			current_y = goal_y - 1;
		}
	}

	if (delta.x < 0 && slope < 0) //x decreasing, y increasing
	{
		int current_y = start_px.y;

		for (int i = 0; i >= delta.x; i--)
		{
			int current_x = start_px.x + i; //we're currently filling in the line at this x value

			int goal_y = std::min(static_cast<int>(std::round(start_px.y + slope * i)), end_px.y);

			for (int j = current_y; j <= goal_y; j++)
			{
				out.push_back({ current_x, j });
			}

			current_y = goal_y + 1;
		}
	}

	if (out.back() != end_px)
	{
		out.push_back(end_px);
	}

	return out;
}
