#pragma once

#include "BinParticle.h"

#define DRAW_FORCES
#define USE_INVSQRT

class ParticleSystem {
protected:
	float timeStep;
	vector<BinParticle> particles;
	vector< vector<BinParticle*> > bins;
	int width, height, k, xBins, yBins, binSize;

public:
	ParticleSystem();

	void setup(int width, int height, int k);
	void setTimeStep(float timeStep);

	void add(BinParticle bParticle);
	vector<BinParticle*> getNeighbors(BinParticle& bParticle, float radius);
	vector<BinParticle*> getNeighbors(float x, float y, float radius);
	vector<BinParticle*> getRegion(unsigned minX, unsigned minY, unsigned maxX, unsigned maxY);
	unsigned size() const;
	BinParticle& operator[](unsigned i);

	void setupForces();
	void addRepulsionForce(const BinParticle& bParticle, float radius, float scale);
	void addRepulsionForce(float x, float y, float radius, float scale);
	void addAttractionForce(const BinParticle& bParticle, float radius, float scale);
	void addAttractionForce(float x, float y, float radius, float scale);
	void addForce(const BinParticle& bParticle, float radius, float scale);
	void addForce(float x, float y, float radius, float scale);
	void update();

	void draw();
};

inline float InvSqrt(float x){
	float xhalf = 0.5f * x;
	int i = *(int*)&x; // store floating-point bits in integer
	i = 0x5f3759d5 - (i >> 1); // initial guess for Newton's method
	x = *(float*)&i; // convert new bits into float
	x = x*(1.5f - xhalf*x*x); // One round of Newton's method
	return x;
}

