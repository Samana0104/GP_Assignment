
#include "Ball.h"
#include "G2W.h"
#include "SDL_image.h"
#include <cmath>
#include <iostream>




Ball::Ball(double radius, Room *room)
{
	room_ = room;
	radius_ = radius;
	isMoving = false;
	
	v_[0] = 0;
	v_[1] = 0;

	mass_ = 2; // 2kg
	coeff_of_restitution_ = 0.7;

	Reset();
}

void Ball::Reset()
{
	p_[0] = radius_ + room_->left_wall_x();
	p_[1] = radius_;

	v_[0] = 0;
	v_[1] = 0;
}

void Ball::Launch(double initial_force_x, double initial_force_y)
{
	v_[0] = v_[0] + (initial_force_x/mass_);
	v_[1] = v_[1] + (initial_force_y/mass_);
	isMoving = true;
}


void Ball::Update(double timestep_s)
{
	double dt = timestep_s;	// seconds
	// 가속도
	double a[2];
	a[0] = 0;
	a[1] = room_->gravitational_acc_y();// Gravity

	// Move
	p_[0] = p_[0] + dt * v_[0];
	p_[1] = p_[1] + dt * v_[1];


	// Collision with Ground
	if ( p_[1] - radius_ < room_->ground_height() && v_[1] < 0 ) 
	{
		p_[1] = radius_ + room_->ground_height();

		v_[1] = -1*v_[1];

		/*
		땅에 있는 조건을 만들기 위해 0.1 오차 감안하고 y축 속도 벡터의 속도를 0으로 바꿔버림
		*/
		if (v_[1] >= 0.1)
			v_[1] = coeff_of_restitution_ * v_[1];
		else
			v_[1] = 0;
	}

	// Collision with Ceilling
	else if ( p_[1]+radius_ > room_->height() && v_[1] > 0 ) 
	{
		p_[1] = room_->height() - radius_;

		v_[1] = -1*v_[1];

		// Coefficient of restitution
	}

	// Collision with Left Wall
	if ( p_[0] - radius_ < room_->left_wall_x() && v_[0] < 0 )
	{
		p_[0] = room_->left_wall_x() + radius_;

		v_[0] = -1 * v_[0];

		// Coefficient of restitution
		//v_[0] = coeff_of_restitution_ * v_[0];

		v_[0] = coeff_of_restitution_ * v_[0];
	}
	// Collision with Right Wall
	else if (p_[0] + radius_ > room_->right_wall_x() && v_[0] > 0)
	{
		p_[0] = room_->right_wall_x() - radius_;

		v_[0] = -1 * v_[0];

		// Coefficient of restitution

		v_[0] = coeff_of_restitution_ * v_[0];
	}
	
	// 울타리 충돌 구현 코드
	if (p_[1] < room_->vertiacal_fence_height() && abs(p_[0] - room_->vertiacal_fence_pos_x()) <= radius_)
	{
		if (v_[0] >= 0)
		{
			p_[0] = room_->vertiacal_fence_pos_x() - radius_;
		}
		else
		{
			p_[0] = room_->vertiacal_fence_pos_x() + radius_;
		}

		v_[0] = -1 * v_[0];
		v_[0] = coeff_of_restitution_ * v_[0];
	}
	else if (p_[1] > room_->vertiacal_fence_height() && sqrt(pow(p_[0] - room_->vertiacal_fence_pos_x(), 2) + pow(p_[1] - room_->vertiacal_fence_height(), 2)) <= radius_)
	{
		double radian = 0;

		if (v_[1] > 0)
		{
			if (v_[0] > 0)
			{
				radian = acos(v_[0] / sqrt(pow(v_[0], 2) + pow(v_[1], 2)));
				v_[0] = v_[0] * cos(radian) + v_[0] * -sin(radian);
				v_[1] = v_[1] * sin(radian) + v_[1] * cos(radian);
			}
			else
			{
				radian = acos(-v_[0] / sqrt(pow(v_[0], 2) + pow(v_[1], 2)));
				v_[0] = v_[0] * cos(radian) + v_[0] * -sin(radian);
				v_[1] = v_[1] * sin(radian) + v_[1] * cos(radian);
			}
			p_[1] = p_[1] + radius_ * sin(radian);
		}
		else
		{
			if (v_[0] > 0)
			{
				radian = acos(-v_[1] / sqrt(pow(v_[0], 2) + pow(v_[1], 2)));
				v_[0] = v_[0] * cos(radian) + v_[0] * sin(radian);
				v_[1] = v_[1] * -sin(radian) + v_[1] * cos(radian);
				if (p_[0] <= room_->vertiacal_fence_pos_x())
				{
					v_[0] *= -1;
					p_[0] = p_[0] - radius_ * cos(radian);
				}
				else
				{
					p_[0] = p_[0] + radius_ * cos(radian);
				}

			}
			else
			{
				radian = acos(-v_[1] / sqrt(pow(v_[0], 2) + pow(v_[1], 2)));
				v_[0] = v_[0] * cos(radian) + v_[0] * sin(radian);
				v_[1] = v_[1] * -sin(radian) + v_[1] * cos(radian);

				if (p_[0] >= room_->vertiacal_fence_pos_x())
				{
					v_[0] *= -1;
					p_[0] = p_[0] + radius_ * cos(radian);
				}
				else
				{
					p_[0] = p_[0] - radius_ * cos(radian);
				}

			}
		}
	}


	/*
	마찰 구현 부분
	*/
	if (v_[0] != 0 && v_[1] == 0 && p_[1] - radius_ == 0)
	{
		if (v_[0] >= -0.1 && v_[0] <= 0.1)
		{
			v_[0] = 0;
			this->isMoving = false;
		}
		else if (v_[0] > 0)
		{
			v_[0] -= 0.05;
		}
		else
		{
			v_[0] += 0.05;
		}
	}
	
	//std::cout << "test2 : " <<p_[0] << ", " << p_[1] << std::endl;

	//속도 = 이전속도 + 시간(dt) * 가속도;
	v_[0] = v_[0] + dt * a[0];
	v_[1] = v_[1] + dt * a[1];
}

void Ball::viewRouteOfBall(SDL_Renderer* renderer, SDL_Texture* ball_texture, SDL_Rect& src, double x, double y)
{
	// 가속도
	double view_a[2];
	double view_v[2];
	double view_p[2];
	double numForFlame = 1.0f / 60.0f;
	double dt;
	double win_radius;
	SDL_Rect dest_rect;

	win_radius = G2W_Scale * this->radius();
	dest_rect.w = (int)(2 * win_radius);
	dest_rect.h = (int)(2 * win_radius);

	view_a[0] = 0.0;
	view_a[1] = room_->gravitational_acc_y();// Gravity

	view_p[0] = radius_ + room_->left_wall_x();
	view_p[1] = radius_;

	view_v[0] = 0;
	view_v[1] = 0;

	view_v[0] = view_v[0] + (x / mass_);
	view_v[1] = view_v[1] + (y / mass_);

	SDL_SetTextureAlphaMod(ball_texture, 100);
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			view_p[0] = view_p[0] + numForFlame * view_v[0];
			view_p[1] = view_p[1] + numForFlame * view_v[1];

			if (view_p[1] - radius_ < room_->ground_height() && view_v[1] < 0)
			{
				view_p[1] = radius_ + room_->ground_height();

				view_v[1] = -1 * view_v[1];


				if (view_v[1] >= 0.1)
					view_v[1] = coeff_of_restitution_ * view_v[1];
				else
					view_v[1] = 0;
			}
			// Collision with Ceilling
			else if (view_p[1] + radius_ > room_->height() && view_v[1] > 0)
			{
				view_p[1] = room_->height() - radius_;

				view_v[1] = -1 * view_v[1];

				// Coefficient of restitution
			}


			// Collision with Left Wall
			if (view_p[0] - radius_ < room_->left_wall_x() && view_v[0] < 0)
			{
				view_p[0] = room_->left_wall_x() + radius_;

				view_v[0] = -1 * view_v[0];

				// Coefficient of restitution
				view_v[0] = coeff_of_restitution_ * view_v[0];
			}
			// Collision with Right Wall
			else if (view_p[0] + radius_ > room_->right_wall_x() && view_v[0] > 0)
			{
				view_p[0] = room_->right_wall_x() - radius_;

				view_v[0] = -1 * view_v[0];

				// Coefficient of restitution

				view_v[0] = coeff_of_restitution_ * view_v[0];
			}

			/* 울타리 충돌 코드 */
			if (view_p[1] < room_->vertiacal_fence_height() && abs(view_p[0] - room_->vertiacal_fence_pos_x()) <= radius_)
			{
				if (view_v[0] >= 0)
				{
					view_p[0] = room_->vertiacal_fence_pos_x() - radius_;
				}
				else
				{
					view_p[0] = room_->vertiacal_fence_pos_x() + radius_;
				}

				view_v[0] = -1 * view_v[0];
				view_v[0] = coeff_of_restitution_ * view_v[0];
			}
			else if (view_p[1] > room_->vertiacal_fence_height() && sqrt(pow(view_p[0] - room_->vertiacal_fence_pos_x(), 2) + pow(view_p[1] - room_->vertiacal_fence_height(), 2)) <= radius_)
			{
				double radian = 0;

				if (view_v[1] > 0)
				{
					if (view_v[0] > 0)
					{
						radian = acos(view_v[0] / sqrt(pow(view_v[0], 2) + pow(view_v[1], 2)));
						view_v[0] = view_v[0] * cos(radian) + view_v[0] * -sin(radian);
						view_v[1] = view_v[1] * sin(radian) + view_v[1] * cos(radian);
					}
					else
					{
						radian = acos(-view_v[0] / sqrt(pow(view_v[0], 2) + pow(view_v[1], 2)));
						view_v[0] = view_v[0] * cos(radian) + view_v[0] * -sin(radian);
						view_v[1] = view_v[1] * sin(radian) + view_v[1] * cos(radian);
					}

					view_p[1] = view_p[1] + radius_ * sin(radian);
				}
				else
				{
					if (view_v[0] > 0)
					{
						radian = acos(-view_v[1] / sqrt(pow(view_v[0], 2) + pow(view_v[1], 2)));
						view_v[0] = view_v[0] * cos(radian) + view_v[0] * sin(radian);
						view_v[1] = view_v[1] * -sin(radian) + view_v[1] * cos(radian);

						if (view_p[0] <= room_->vertiacal_fence_pos_x())
						{
							view_v[0] *= -1;
							view_p[0] = view_p[0] - radius_ * cos(radian);
						}
						else
						{
							view_p[0] = view_p[0] + radius_ * cos(radian);
						}
					}
					else
					{
						radian = acos(-view_v[1] / sqrt(pow(view_v[0], 2) + pow(view_v[1], 2)));
						view_v[0] = view_v[0] * cos(radian) + view_v[0] * sin(radian);
						view_v[1] = view_v[1] * -sin(radian) + view_v[1] * cos(radian);

						if (view_p[0] >= room_->vertiacal_fence_pos_x())
						{
							view_v[0] *= -1;
							view_p[0] = view_p[0] + radius_ * cos(radian);
						}
						else
						{
							view_p[0] = view_p[0] - radius_ * cos(radian);
						}
					}
				}
			}

			view_v[0] = view_v[0] + numForFlame *view_a[0];
			view_v[1] = view_v[1] + numForFlame *view_a[1];
		}


		//속도 = 이전속도 + 시간(dt) * 가속도;

		dest_rect.x = (int)(G2W_X(view_p[0]) - win_radius);
		dest_rect.y = (int)(G2W_Y(view_p[1]) - win_radius);

		SDL_RenderCopy(renderer, ball_texture, &src, &dest_rect);
	}

	SDL_SetTextureAlphaMod(ball_texture, 255);
}