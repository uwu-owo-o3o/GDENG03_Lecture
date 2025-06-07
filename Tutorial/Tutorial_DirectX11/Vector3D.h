#pragma once

class Vector3D 
{
	public:
		Vector3D() : m_x(0), m_y(0), m_z(0)
		{


		}

		Vector3D(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
		{


		}

		Vector3D(const Vector3D& vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z)
		{

		}

		static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta) 
		{
			Vector3D v;
			v.m_x = start.m_x * (1.0f - delta) + end.m_x;
			v.m_y = start.m_y * (1.0f - delta) + end.m_y;
			v.m_z = start.m_z * (1.0f - delta) + end.m_z;

			return v;
		}

		Vector3D operator *(float num) {
			return Vector3D(m_x * num, m_y * num, m_z * num);
		}

		Vector3D operator +(Vector3D vector) {
			return Vector3D(m_x + vector.m_x, m_y + vector.m_y, m_z + vector.m_z);
		}

		Vector3D operator /(float num) {
			return Vector3D(m_x / num, m_y / num, m_z / num);
		}

		Vector3D operator -(Vector3D vector) {
			return Vector3D(m_x - vector.m_x , m_y - vector.m_y, m_z - vector.m_z);
		}

		static Vector3D Normalize(Vector3D vector) 
		{
			Vector3D v;
			float magnitude = sqrt(powf(vector.m_x, 2) + powf(vector.m_y, 2) + powf(vector.m_z, 2));
			if (magnitude == 0) {
				v = Vector3D(0, 0, 0);
			}
			else {
				v = vector / magnitude;
			}
			
			return v;
		} 

		~Vector3D() 
		{

		}

	public:
		float m_x;
		float m_y;
		float m_z;

};