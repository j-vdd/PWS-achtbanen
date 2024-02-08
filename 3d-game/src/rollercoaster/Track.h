#pragma once

#include <iostream>

#include "common.h"

using namespace math;

#include "graphics/Mesh.h"
#include "graphics/Material.h"

inline void generateGraph(std::vector<float>& vertices, std::vector<uint32_t>& indices, const std::vector<DVec2>& dataPoints, const Vec2& position, bool log)
{
	double minValue = 100000.0;
	double maxValue = 0.0;
	for (auto& d : dataPoints)
	{
		double v = d.y;
		minValue = std::min(v, minValue);
		maxValue = std::max(v, maxValue);
	}

	auto pushVertex = [&](float x, float y)
		{
			vertices.insert(vertices.end(), { x + position.x, y + position.y });
		};

	pushVertex(0.0f, 0.0f);
	pushVertex(0.0f, float(dataPoints[0].y));
	double prev = 1;
	for (size_t i = 1; i < dataPoints.size(); i++)
	{
		const DVec2& d = dataPoints[i];
		double v = d.y;

		uint32_t s = uint32_t(vertices.size() / 2 - 2);
		indices.insert(indices.end(), {
			s + 0, s + 1, s + 2,
			s + 1, s + 2, s + 3
		});

		//y / x = c, sqrt(x^2 + y^2) = n
		//
		//sqrt(c^2 + 1) = 0.1f / x
		double slope = (dataPoints[i].y - dataPoints[i - 1].y) / (dataPoints[i].x - dataPoints[i - 1].x);
		if (log)
			std::cout << dataPoints[i].y << ", " << slope << std::endl;

		double offset = sqrt(slope * slope + 1);
		
		//if (abs(offset - prev) > 0.7)
		//{
		//	offset = std::min(offset, 9.0);
		//	//prev = offset;
		//	//continue;
		//}
			//offset = (offset + prev * 15) / 16;

		pushVertex(float(d.x), float(dataPoints[i].y - 0.05 * offset));
		pushVertex(float(d.x), float(dataPoints[i].y + 0.05 * offset));

		prev = offset;
	}
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
	os << "x: " << v.x << ", y: " << v.y << ", z: " << v.z;
	return os;
}

class Cubic
{
public:
	Cubic() {}
	Cubic(const DVec2& _extremum1, const DVec2& _extremum2)
		: extremum1(_extremum1), extremum2(_extremum2)
	{}

	double sample(double x) const
	{
		x /= extremum2.x - extremum1.x;
		x += extremum1.x;

		//return (x) * (extremum2.y - extremum1.y) + extremum1.y;
		//return (sin(x * 3.141592 / 2.0) * sin(x * 3.141592 / 2.0)) * (extremum2.y - extremum1.y) + extremum1.y;
		return (-2.0 * x * x * x + 3.0 * x * x) * (extremum2.y - extremum1.y) + extremum1.y;
	}

private:
	DVec2 extremum1, extremum2;
};

struct ForceFrame
{
	ForceFrame()
	{}
	ForceFrame(const DVec3& _X, const DVec3& _T, const DVec3& _N, double _v)
	{
		X = _X;
		V = _T * _v;
		v = _v;
		T = _T;
		N = _N;
		B = cross(_N, _T);
	}

	DVec3 X;
	DVec3 V;
	double v;
	DVec3 T; //unnecessary, but useful
	DVec3 B;
	DVec3 N;
};

inline DVec3 rotateBaseVector(const DVec3& v, const DVec3& normalizedAxis, double angle)
{
	const DVec3 along = dot(v, normalizedAxis) * normalizedAxis;
	const DVec3 side = cross(normalizedAxis, v);
	const DVec3 up = v - along; //direction of v perpendicular to axis
	
	return along + cos(angle) * up + sin(angle) * side;
}

struct Cart
{
	double g = 9.81;
	double mass = 3000.0;
	double E = g * mass * 50.0 + 0.5 * mass * (2.0 * 2.0);
	
	double rolCoefficient = 0.009;

	double calcCurrentSpeed(const DVec3& position)
	{
		double E_gravity = mass * g * position.y;
		double E_k = E - E_gravity;

		return sqrt(2.0 * E_k / mass);
	}
	double predictNewSpeed(const ForceFrame& f0, double f, double dt)
	{
		DVec3 predictedPosition = f0.X + f0.V * dt;
		double E_gravity = mass * g * predictedPosition.y;
		double F_normal = abs(f) * mass;
		double F_rol = rolCoefficient * F_normal;
		double F_lucht = 0;// mass* powf(f0.v, 2.0f) * 0.0001f;

		double E_weerstand = (F_rol + F_lucht) * f0.v * dt;
		double E_k = E - E_gravity - E_weerstand;

		return sqrt(2.0 * E_k / mass);
	}
	double calcNewSpeed(const ForceFrame& f0, DVec3 X1, double f, double dt)
	{
		double E_gravity = mass * g * X1.y;
		double F_normal = abs(f) * mass;
		double F_rol = rolCoefficient * F_normal;
		double F_lucht = 0;// mass* powf(f0.v, 2.0f) * 0.0001f;
		
		double E_weerstand = (F_rol + F_lucht) * length(f0.X - X1);
		E -= E_weerstand;
		double E_k = E - E_gravity;
		
		return sqrt(2.0 * E_k / mass);
	}
};

constexpr double dt = 0.001;

inline ForceFrame generateNext(const ForceFrame& Frame0, Cart& cart, double f, double omega, double dt)
{
	const DVec3 G = DVec3(0, -cart.g, 0);

	const double v0 = Frame0.v;
	double v1 = cart.predictNewSpeed(Frame0, f, dt);
	double dv = (v1 - v0) / dt;

	const DVec3 C = -dv * Frame0.T - dot(Frame0.B, G) * Frame0.B + G;
	const double NdC = dot(Frame0.N, C);

	const double sign = f <= 0.0 ? -1.0 : 1.0;
	
	double D = NdC * NdC + f * f - dot(C, C);
	if (D > -0.001)
	{
		D = std::max(0.0, D);
	}

	const double k = (-NdC + sign * sqrt(D)) / v0;
	const double l = dot(Frame0.B, G) / v0;

	const DVec3 W = omega * Frame0.T + k * Frame0.B + l * Frame0.N;
	if (length(W) <= 0.001)
	{
		const DVec3 X1 = Frame0.X + Frame0.V * dt;

		return ForceFrame(X1, Frame0.T, Frame0.N, v1);
	}

	const DVec3 I = normalize(W);
	const DVec3 J = Frame0.V - dot(Frame0.V, I) * I;
	const DVec3 K = cross(I, J);

	const double c = cos(length(W) * dt);
	const double s = sin(length(W) * dt);

	const DVec3 X1 = Frame0.X + K / length(W) + dot(Frame0.T * v0, I) * I * dt + s * J / length(W) - c * K / length(W);

	const DVec3 N1 = rotateBaseVector(Frame0.N, I, length(W) * dt);
	const DVec3 T1 = rotateBaseVector(Frame0.T, I, length(W) * dt);

	v1 = cart.calcNewSpeed(Frame0, X1, f, dt);
	return ForceFrame(X1, T1, N1, v1);
}

class ForceSegment
{
public:
	ForceSegment(double f_0, double f_1, double omega_0, double omega_1, double duration)
	{
		m_f = Cubic(DVec2(0, f_0), DVec2(duration, f_1));
		m_omega = Cubic(DVec2(0, omega_0), DVec2(duration, omega_1));
		m_Duration = duration;
	}

	void generate(Cart& cart, std::vector<ForceFrame>& frames)
	{
		ForceFrame prevFrame = frames.back();
		for (double time = 0.0; time < m_Duration; time += dt)
		{
			ForceFrame nextFrame = generateNext(prevFrame, cart, m_f.sample(time), m_omega.sample(time), dt);
			frames.push_back(nextFrame);
			
			prevFrame = nextFrame;
		}
	}

	double getForceFromTime(double time) const
	{
		return m_f.sample(time);
	}
	double getOmegaFromTime(double time) const
	{
		return m_omega.sample(time);
	}
	double duration() const
	{
		return m_Duration;
	}

private:
	Cubic m_f;
	Cubic m_omega;
	double m_Duration;
};

class Track
{
public:
	//<f, omega, t>
	Track(const std::vector<DVec3> segmentDescriptions)
	{
		m_SegmentDescriptions = segmentDescriptions;
		m_SegmentPointer = 0;

		reload();
	}

	std::string save()
	{
		std::string out;
		for (const auto& segment : m_SegmentDescriptions)
		{
			out += std::to_string(segment.x) + ", " + std::to_string(segment.y) + ", " + std::to_string(segment.z) + "\n";
		}
		return out;
	}

	void reload()
	{
		m_Segments.clear();
		m_Frames.clear();
		m_Time = 0.0;
		m_Cart = Cart();

		DVec3 prev = m_SegmentDescriptions[0];
		DVec3 startPos = DVec3(0.0, 50.0, 0.0);

		ForceFrame firstFrame = ForceFrame(startPos, DVec3(0.0, 0.0, -1.0), DVec3(0.0, 1.0, 0.0), m_Cart.calcCurrentSpeed(startPos));
		m_Frames.push_back(firstFrame);

		for (size_t i = 1; i < m_SegmentDescriptions.size(); i++)
		{
			DVec3 cur = m_SegmentDescriptions[i];
			auto forceSegment = ForceSegment(prev.x, cur.x, prev.y, cur.y, cur.z);
			forceSegment.generate(m_Cart, m_Frames);
			m_Segments.push_back(forceSegment);
			m_Time += cur.z;

			prev = cur;
		}
	}

	void graphSpeed(Ref<Mesh>& mesh)
	{
		std::vector<DVec2> velocityData;
		std::vector<DVec2> forceData;
		std::vector<DVec2> forceData2;
		std::vector<DVec2> omegaData;
		std::vector<DVec2> omegaData2;
		
		double graphDt = 0.01;
		double totalTime = 0.0;
		for (size_t i = 0; i < m_Segments.size(); i++)
		{
			double time = 0;
			while (time < m_SegmentDescriptions[i + 1].z)
			{
				forceData.push_back({ time + totalTime, m_Segments[i].getForceFromTime(time) / 9.81 });
				omegaData.push_back({ time + totalTime, m_Segments[i].getOmegaFromTime(time)});

				size_t frameIndex = (size_t)round((totalTime + time) / m_Time * m_Frames.size());
				const ForceFrame& F1 = m_Frames[frameIndex];
				const ForceFrame& F2 = m_Frames[frameIndex + 1];
				forceData2.push_back({ time + totalTime, length((F2.V - F1.V) / dt + DVec3(0, m_Cart.g, 0)) / 9.81 * (m_Segments[i].getForceFromTime(time) < 0 ? -1 : 1) });

				velocityData.push_back({ time + totalTime, m_Frames[frameIndex].v });

				DVec3 w1 = (F1.T - F2.T) / dt;
				DVec3 w2 = (F1.N - F2.N) / dt;
				DVec3 w = normalize(cross(w1, w2));

				w *= length(w1) / length(cross(w, F1.T));
				omegaData2.push_back({ time + totalTime, abs(dot(w, F1.T)) * (m_Segments[i].getOmegaFromTime(time) < 0 ? -1 : 1)});

				time += graphDt;
			}

			totalTime += m_SegmentDescriptions[i + 1].z;
		}

		std::vector<float> vertices;
		std::vector<uint32_t> indices;
		generateGraph(vertices, indices, velocityData, Vec2(200.0f, 0.0f), false);
		generateGraph(vertices, indices, forceData, Vec2(200.0f, -30.0f), false);
		generateGraph(vertices, indices, forceData2, Vec2(200.0f, -10.0f), false);
		generateGraph(vertices, indices, omegaData, Vec2(200.0f, -40.0f), false);
		generateGraph(vertices, indices, omegaData2, Vec2(200.0f, -20.0f), false);

		mesh->setLayout({ 2 });
		mesh->setShape(vertices, indices);
	}

	const ForceFrame& getFrame(double time) const
	{
		time -= m_Time * floor(time / m_Time);

		size_t frameIndex = (size_t)round(time / m_Time * m_Frames.size());
		return m_Frames[frameIndex];
	}

	void generateMesh(Ref<Mesh>& mesh, Ref<Material>& material)
	{
		std::vector<float> vertices;
		std::vector<uint32_t> indices;
		float index = 0.0f;

		double cartHeight = 0.8;
		double tw = 0.5;
		double th = 0.3;
		double r = 0.11;
		double r2 = 0.08;
		double r3 = 0.2;

		auto pushVertexIndex = [&](const DVec3& v, const DVec3& n, const Vec2& t, float i)
			{
				vertices.insert(vertices.end(), {
					(float)v.x, (float)v.y, (float)v.z,
					(float)n.x, (float)n.y, (float)n.z,
					t.x, t.y,
					i
					});
			};
		auto pushVertex = [&](const DVec3& v, const DVec3& n, const Vec2& t)
			{
				vertices.insert(vertices.end(), {
					(float)v.x, (float)v.y, (float)v.z,
					(float)n.x, (float)n.y, (float)n.z,
					t.x, t.y,
					index
				});
			};
		auto insertSegment = [&](const ForceFrame& f1, const ForceFrame& f2, bool isPartition)
			{
				DVec3 P1 = DVec3(0.0, 1.0, 0.0);
				DVec3 P2 = DVec3(sqrt(3.0) / 2.0, -0.5, 0.0);
				DVec3 P3 = DVec3(-sqrt(3.0) / 2.0, -0.5, 0.0);
				DMat3 transform1 = DMat3(f1.B, f1.N, f1.T);
				DMat3 transform2 = DMat3(f2.B, f2.N, f2.T);

				const DVec3 middle1 = f1.X - f1.N * cartHeight;
				const DVec3 middle2 = f2.X - f2.N * cartHeight;

				uint32_t s = (uint32_t)vertices.size() / 9;
				pushVertex(middle1 + f1.B * tw + transform1 * P1 * r, transform1 * P1, Vec2(0, 0));
				pushVertex(middle1 + f1.B * tw + transform1 * P2 * r, transform1 * P2, Vec2(0, 0));
				pushVertex(middle1 + f1.B * tw + transform1 * P3 * r, transform1 * P3, Vec2(0, 0));
				pushVertex(middle2 + f2.B * tw + transform2 * P1 * r, transform2 * P1, Vec2(0, 0));
				pushVertex(middle2 + f2.B * tw + transform2 * P2 * r, transform2 * P2, Vec2(0, 0));
				pushVertex(middle2 + f2.B * tw + transform2 * P3 * r, transform2 * P3, Vec2(0, 0));

				pushVertex(middle1 - f1.B * tw + transform1 * P1 * r, transform1 * P1, Vec2(0, 0));
				pushVertex(middle1 - f1.B * tw + transform1 * P2 * r, transform1 * P2, Vec2(0, 0));
				pushVertex(middle1 - f1.B * tw + transform1 * P3 * r, transform1 * P3, Vec2(0, 0));
				pushVertex(middle2 - f2.B * tw + transform2 * P1 * r, transform2 * P1, Vec2(0, 0));
				pushVertex(middle2 - f2.B * tw + transform2 * P2 * r, transform2 * P2, Vec2(0, 0));
				pushVertex(middle2 - f2.B * tw + transform2 * P3 * r, transform2 * P3, Vec2(0, 0));

				pushVertex(middle1 - f1.N * th - transform1 * P1 * r3, -transform1 * P1, Vec2(0, 0));
				pushVertex(middle1 - f1.N * th - transform1 * P2 * r3, -transform1 * P2, Vec2(0, 0));
				pushVertex(middle1 - f1.N * th - transform1 * P3 * r3, -transform1 * P3, Vec2(0, 0));
				pushVertex(middle2 - f2.N * th - transform2 * P1 * r3, -transform2 * P1, Vec2(0, 0));
				pushVertex(middle2 - f2.N * th - transform2 * P2 * r3, -transform2 * P2, Vec2(0, 0));
				pushVertex(middle2 - f2.N * th - transform2 * P3 * r3, -transform2 * P3, Vec2(0, 0));

				indices.insert(indices.end(), {
					s + 0, s + 1, s + 3,
					s + 1, s + 3, s + 4,
					s + 0, s + 2, s + 3,
					s + 2, s + 3, s + 5,
					s + 1, s + 2, s + 4,
					s + 2, s + 4, s + 5
				});
				
				s += 6;
				indices.insert(indices.end(), {
					s + 0, s + 1, s + 3,
					s + 1, s + 3, s + 4,
					s + 0, s + 2, s + 3,
					s + 2, s + 3, s + 5,
					s + 1, s + 2, s + 4,
					s + 2, s + 4, s + 5,
				});

				s += 6;
				indices.insert(indices.end(), {
					s + 0, s + 1, s + 3,
					s + 1, s + 3, s + 4,
					s + 0, s + 2, s + 3,
					s + 2, s + 3, s + 5,
					s + 1, s + 2, s + 4,
					s + 2, s + 4, s + 5,
				});

				if (isPartition) {
					DVec3 SP1 = DVec3(0.0, 1.0, 0.0);
					DVec3 SP2 = DVec3(0.0, -0.5, sqrt(3.0) / 2.0);
					DVec3 SP3 = DVec3(0.0, -0.5, -sqrt(3.0) / 2.0);

					s = (uint32_t)vertices.size() / 9;
					pushVertex(middle1 + f1.B * tw + transform1 * SP1 * r2, transform1 * SP1, Vec2(0, 0));
					pushVertex(middle1 + f1.B * tw + transform1 * SP2 * r2, transform1 * SP2, Vec2(0, 0));
					pushVertex(middle1 + f1.B * tw + transform1 * SP3 * r2, transform1 * SP3, Vec2(0, 0));
					pushVertex(middle1 - f1.B * tw + transform1 * SP1 * r2, transform1 * SP1, Vec2(0, 0));
					pushVertex(middle1 - f1.B * tw + transform1 * SP2 * r2, transform1 * SP2, Vec2(0, 0));
					pushVertex(middle1 - f1.B * tw + transform1 * SP3 * r2, transform1 * SP3, Vec2(0, 0));
					pushVertex(middle1 - f1.N * th + transform1 * SP1 * r2, transform1 * SP1, Vec2(0, 0));
					pushVertex(middle1 - f1.N * th + transform1 * SP2 * r2, transform1 * SP2, Vec2(0, 0));
					pushVertex(middle1 - f1.N * th + transform1 * SP3 * r2, transform1 * SP3, Vec2(0, 0));

					indices.insert(indices.end(), {
						s + 0, s + 1, s + 6,
						s + 1, s + 6, s + 7,
						s + 0, s + 2, s + 6,
						s + 2, s + 6, s + 8,
						s + 1, s + 2, s + 7,
						s + 2, s + 7, s + 8,

						s + 3, s + 4, s + 6,
						s + 4, s + 6, s + 7,
						s + 3, s + 5, s + 6,
						s + 5, s + 6, s + 8,
						s + 4, s + 5, s + 7,
						s + 5, s + 7, s + 8,
					});
				}
			};

		auto insertSupport = [&](const ForceFrame& f)
			{
				if (f.N.y < -0.3)
					return;

				double supportRadius1 = 0.2;
				double supportRadius2 = 0.5;
				double supportLength1 = 2.5;

				const DVec3 P1 = DVec3(0.0, 0.0, 1.0);
				const DVec3 P2 = DVec3(sqrt(3.0) / 2.0, 0.0, -0.5);
				const DVec3 P3 = DVec3(-sqrt(3.0) / 2.0, 0.0, -0.5);
				DMat3 transform = DMat3(f.B, f.N, f.T);
				DMat3 transformThird = DMat3(normalize(DVec3(f.B.x, 0.0, f.B.z)), DVec3(0.0, 1.0, 0.0), normalize(DVec3(f.T.x, 0.0, f.T.z)));
				DMat3 transformSecond = (transform + transformThird) * 0.5;

				const DVec3 first1 = f.X - f.N * cartHeight + f.B * tw;
				const DVec3 first2 = f.X - f.N * cartHeight - f.B * tw;
				const DVec3 second = f.X - f.N * cartHeight - f.N * supportLength1;
				const DVec3 third = DVec3(second.x, 0.0, second.z);

				uint32_t s = (uint32_t)vertices.size() / 9;
				pushVertexIndex(first1 + transform * P1 * supportRadius1, transform * P1, Vec2(0, 0), -1.0f);
				pushVertexIndex(first1 + transform * P2 * supportRadius1, transform * P2, Vec2(0, 0), -1.0f);
				pushVertexIndex(first1 + transform * P3 * supportRadius1, transform * P3, Vec2(0, 0), -1.0f);
				pushVertexIndex(first2 + transform * P1 * supportRadius1, transform * P1, Vec2(0, 0), -1.0f);
				pushVertexIndex(first2 + transform * P2 * supportRadius1, transform * P2, Vec2(0, 0), -1.0f);
				pushVertexIndex(first2 + transform * P3 * supportRadius1, transform * P3, Vec2(0, 0), -1.0f);

				transform[1] = Vec3(0.0f);
				pushVertexIndex(second + transform * P1 * supportRadius2, transformSecond * P1, Vec2(0, 0), -1.0f);
				pushVertexIndex(second + transform * P2 * supportRadius2, transformSecond * P2, Vec2(0, 0), -1.0f);
				pushVertexIndex(second + transform * P3 * supportRadius2, transformSecond * P3, Vec2(0, 0), -1.0f);
				pushVertexIndex(third + transformThird * P1 * supportRadius2, P1, Vec2(0, 0), -1.0f);
				pushVertexIndex(third + transformThird * P2 * supportRadius2, P2, Vec2(0, 0), -1.0f);
				pushVertexIndex(third + transformThird * P3 * supportRadius2, P3, Vec2(0, 0), -1.0f);

				indices.insert(indices.end(), {
					s + 0, s + 1, s + 6,
					s + 1, s + 6, s + 7,
					s + 0, s + 2, s + 6,
					s + 2, s + 6, s + 8,
					s + 1, s + 2, s + 7,
					s + 2, s + 7, s + 8,
				});
				indices.insert(indices.end(), {
					s + 3, s + 4, s + 6,
					s + 4, s + 6, s + 7,
					s + 3, s + 5, s + 6,
					s + 5, s + 6, s + 8,
					s + 4, s + 5, s + 7,
					s + 5, s + 7, s + 8,
				});
				indices.insert(indices.end(), {
					s + 9, s + 10, s + 6,
					s + 10, s + 6, s + 7,
					s + 9, s + 11, s + 6,
					s + 11, s + 6, s + 8,
					s + 10, s + 11, s + 7,
					s + 11, s + 7, s + 8,
				});
			};

		ForceFrame prevFrame = m_Frames[0];
		ForceFrame prevMeshFrame = prevFrame;
		insertSupport(prevMeshFrame);

		double distance = 0.0;
		double subDistance = 0.0;
		
		double segmentTime = 0;
		size_t segmentIndex = 0;
		for (size_t frameIndex = 1; frameIndex < m_Frames.size(); frameIndex++)
		{
			ForceFrame nextFrame = m_Frames[frameIndex];

			double ds = length((nextFrame.X - nextFrame.N * cartHeight) - (prevFrame.X - prevFrame.N * cartHeight));
			distance += ds;
			subDistance += ds;

			if (distance >= 0.5)
			{
				distance -= 0.5;
				bool hasSub = false;
				if (subDistance >= 2.0)
				{
					hasSub = true;
					subDistance -= 2.0;
				}

				insertSegment(prevMeshFrame, nextFrame, hasSub);
				prevMeshFrame = nextFrame;
			}

			prevFrame = nextFrame;

			auto& segment = m_Segments[segmentIndex];
			double time = double(frameIndex) / double(m_Frames.size()) * m_Time;
			if (time - segmentTime > segment.duration())
			{
				insertSupport(prevMeshFrame);

				index += 1.0f;
				segmentTime += segment.duration();
				segmentIndex++;
			}
		}

		mesh->setShape(vertices, indices);
		mesh->setLayout({ 3, 3, 2, 1 });
	}

	void incrementSegmentPointer(Ref<Mesh>& trackMesh, Ref<Material>& trackMaterial, Ref<Mesh>& graphMesh)
	{
		m_SegmentPointer++;
		if (m_SegmentPointer >= m_Segments.size())
		{
			DVec3& prev = m_SegmentDescriptions.back();
			m_SegmentDescriptions.push_back(DVec3(prev.x, prev.y, 1.0));
			reload();
			generateMesh(trackMesh, trackMaterial);
			graphSpeed(graphMesh);
		}
		trackMaterial->set("trackIndex", float(m_SegmentPointer));

		DVec3& segmentDescription = m_SegmentDescriptions[m_SegmentPointer + 1];
		std::cout << "force: " << segmentDescription.x / 9.81 << ", omega: " << segmentDescription.y << ", time: " << segmentDescription.z << std::endl;
	}
	void decrementSegmentPointer(Ref<Mesh>& trackMesh, Ref<Material>& trackMaterial)
	{
		if (m_SegmentPointer == 0)
			return;

		m_SegmentPointer--;
		trackMaterial->set("trackIndex", float(m_SegmentPointer));

		DVec3& segmentDescription = m_SegmentDescriptions[m_SegmentPointer + 1];
		std::cout << "force: " << segmentDescription.x / 9.81 << ", omega: " << segmentDescription.y << ", time: " << segmentDescription.z << std::endl;
	}

	void changeLastSegment(Ref<Mesh>& trackMesh, Ref<Material>& trackMaterial, double dForce, double dOmega, double dTime, Ref<Mesh>& graphMesh)
	{
		DVec3& segmentDescription = m_SegmentDescriptions[m_SegmentPointer + 1];

		segmentDescription += Vec3(dForce, dOmega, dTime);
		std::cout << "force: " << segmentDescription.x / 9.81 << ", omega: " << segmentDescription.y << ", time: " << segmentDescription.z << std::endl;

		reload();
		generateMesh(trackMesh, trackMaterial);
		graphSpeed(graphMesh);
	}

private:
	size_t m_SegmentPointer;
	double m_Time;
	std::vector<DVec3> m_SegmentDescriptions;
	std::vector<ForceFrame> m_Frames;
	Cart m_Cart;

	std::vector<ForceSegment> m_Segments;
};