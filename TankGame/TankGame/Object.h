#ifndef __OBJECT_H__
#define __OBJECT_H__

class Object {
public:
	virtual bool Initialize(void *arg) = 0;
	virtual bool Update() = 0;
	virtual bool Render() = 0;
	virtual bool Destroy() = 0;

};

#endif ///> end of __OBJECT_H__