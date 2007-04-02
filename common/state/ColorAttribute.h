#ifndef COLORATTRIBUTE_H
#define COLORATTRIBUTE_H
#include <state_exports.h>
#include <AttributeSubject.h>

// ****************************************************************************
// Class: ColorAttribute
//
// Purpose:
//    This class contains RGBA color information
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Fri Mar 31 16:58:56 PST 2006
//
// Modifications:
//   
// ****************************************************************************

class STATE_API ColorAttribute : public AttributeSubject
{
public:
    ColorAttribute();
    ColorAttribute(const ColorAttribute &obj);
    virtual ~ColorAttribute();

    virtual ColorAttribute& operator = (const ColorAttribute &obj);
    virtual bool operator == (const ColorAttribute &obj) const;
    virtual bool operator != (const ColorAttribute &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectColor();

    // Property setting methods
    void SetColor(const unsigned char *color_);

    // Property getting methods
    const unsigned char *GetColor() const;
          unsigned char *GetColor();

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);


    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

    // User-defined methods
    ColorAttribute(int red, int green, int blue, int alpha = 255);
    void SetRgb(int red, int green, int blue);
    void SetRgba(int red, int green, int blue, int alpha);
    void GetRgba(double c[4]) const;
    void SetRed(int red);
    void SetGreen(int green);
    void SetBlue(int blue);
    void SetAlpha(int alpha);
    int Red() const;
    int Green() const;
    int Blue() const;
    int Alpha() const;
    void SetRgba2(double c[4]);
private:
    unsigned char color[4];
};

#endif
