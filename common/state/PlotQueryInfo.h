#ifndef PLOTQUERYINFO_H
#define PLOTQUERYINFO_H
#include <state_exports.h>
#include <string>
#include <AttributeSubject.h>

// ****************************************************************************
// Class: PlotQueryInfo
//
// Purpose:
//    This class is a .
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Jul 15 13:47:47 PST 2003
//
// Modifications:
//   
// ****************************************************************************

class STATE_API PlotQueryInfo : public AttributeSubject
{
public:
    enum ChangeType
    {
        None,
        Database,
        VarName,
        AddOp,
        OpAtts,
        PlotAtts,
        MoveOperator,
        RemoveOperator,
        RemoveAll,
        RemoveLast
    };

    PlotQueryInfo();
    PlotQueryInfo(const PlotQueryInfo &obj);
    virtual ~PlotQueryInfo();

    virtual void operator = (const PlotQueryInfo &obj);
    virtual bool operator == (const PlotQueryInfo &obj) const;
    virtual bool operator != (const PlotQueryInfo &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;

    // Property selection methods
    virtual void SelectAll();

    // Property setting methods
    void SetChangeType(ChangeType changeType_);

    // Property getting methods
    ChangeType GetChangeType() const;

    // Enum conversion functions
    static std::string ChangeType_ToString(ChangeType);
    static bool ChangeType_FromString(const std::string &, ChangeType &);
protected:
    static std::string ChangeType_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

private:
    int changeType;
};

#endif
