/*
 * modelViewer.h
 *
 *  Created on: 14 Oct 2010
 *      Author: Ziggy
 */

#ifndef MODELVIEWER_H_
#define MODELVIEWER_H_
#include <vectormath/scalar/cpp/vectormath_aos.h>
#include <vector>

using namespace std;

struct tmpInts{
	int prev;
	int newv;
	tmpInts(int i, int k){prev = i; newv = k;};
};

struct edge{
	unsigned int start;
	unsigned int stop;
	edge(int i, int k){start = i;stop = k;};
	unsigned int halfPoint;//for catmull clark
};
struct face{
	int edge[4];
	face(int i, int k, int j, int l){edge[0] = i; edge[1]=k; edge[2]=j; edge[3]=l;};
	unsigned int facePoint; //for catmull clark
};

class ModelViewer{
private:
	vector<face> faces;
	vector<Vectormath::Aos::Vector3> coordList;
	vector<edge>edges;
	int sides;

public:
	void draw();
	void setCoords();
	void setTriangles();
	void setEdges();
	ModelViewer();
	~ModelViewer();
	Vectormath::Aos::Vector3 findHalfPoint(unsigned int edge);
	Vectormath::Aos::Vector3 findHalfPointUsingFace(unsigned int edge);
	void drawHalfPoints();
	void drawEdges();
	void subDivide();
	void reset();
	int toAbsolute(int x);
	void catmullClark();
};

#endif /* MODELVIEWER_H_ */
