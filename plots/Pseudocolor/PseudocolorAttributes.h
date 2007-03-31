#ifndef PSEUDOCOLORATTRIBUTES_H
#define PSEUDOCOLORATTRIBUTES_H
#include <string>
#include <AttributeSubject.h>
#include <iostream.h>

// ****************************************************************************
// Class: PseudocolorAttributes
//
// Purpose:
//    Attributes for the pseudocolor plot
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Jul 15 13:57:51 PST 2003
//
// Modifications:
//   
// ****************************************************************************

class PseudocolorAttributes : public AttributeSubject
{
public:
    enum Centering
    {
        Natural,
        Nodal,
        Zonal
    };
    enum Scaling
    {
        Linear,
        Log,
        Skew
    };
    enum LimitsMode
    {
        OriginalData,
        CurrentPlot
    };

    PseudocolorAttributes();
    PseudocolorAttributes(const PseudocolorAttributes &obj);
    virtual ~PseudocolorAttributes();

    virtual void operator = (const PseudocolorAttributes &obj);
    virtual bool operator == (const PseudocolorAttributes &obj) const;
    virtual bool operator != (const PseudocolorAttributes &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectColorTableName();
    void SelectPointSizeVar();

    // Property setting methods
    void SetLegendFlag(bool legendFlag_);
    void SetLightingFlag(bool lightingFlag_);
    void SetMinFlag(bool minFlag_);
    void SetMaxFlag(bool maxFlag_);
    void SetCentering(Centering centering_);
    void SetScaling(Scaling scaling_);
    void SetLimitsMode(LimitsMode limitsMode_);
    void SetMin(double min_);
    void SetMax(double max_);
    void SetPointSize(double pointSize_);
    void SetSkewFactor(double skewFactor_);
    void SetOpacity(double opacity_);
    void SetColorTableName(const std::string &colorTableName_);
    void SetSmoothingLevel(int smoothingLevel_);
    void SetPointSizeVarEnabled(bool pointSizeVarEnabled_);
    void SetPointSizeVar(const std::string &pointSizeVar_);

    // Property getting methods
    bool              GetLegendFlag() const;
    bool              GetLightingFlag() const;
    bool              GetMinFlag() const;
    bool              GetMaxFlag() const;
    Centering         GetCentering() const;
    Scaling           GetScaling() const;
    LimitsMode        GetLimitsMode() const;
    double            GetMin() const;
    double            GetMax() const;
    double            GetPointSize() const;
    double            GetSkewFactor() const;
    double            GetOpacity() const;
    const std::string &GetColorTableName() const;
          std::string &GetColorTableName();
    int               GetSmoothingLevel() const;
    bool              GetPointSizeVarEnabled() const;
    const std::string &GetPointSizeVar() const;
          std::string &GetPointSizeVar();

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool forceAdd);
    virtual void SetFromNode(DataNode *node);

    // Enum conversion functions
    static std::string Centering_ToString(Centering);
    static bool Centering_FromString(const std::string &, Centering &);
protected:
    static std::string Centering_ToString(int);
public:
    static std::string Scaling_ToString(Scaling);
    static bool Scaling_FromString(const std::string &, Scaling &);
protected:
    static std::string Scaling_ToString(int);
public:
    static std::string LimitsMode_ToString(LimitsMode);
    static bool LimitsMode_FromString(const std::string &, LimitsMode &);
protected:
    static std::string LimitsMode_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

    // User-defined methods
    bool ChangesRequireRecalculation(const PseudocolorAttributes &) const;
    void Print(ostream &, bool) const;
private:
    bool        legendFlag;
    bool        lightingFlag;
    bool        minFlag;
    bool        maxFlag;
    int         centering;
    int         scaling;
    int         limitsMode;
    double      min;
    double      max;
    double      pointSize;
    double      skewFactor;
    double      opacity;
    std::string colorTableName;
    int         smoothingLevel;
    bool        pointSizeVarEnabled;
    std::string pointSizeVar;
};

#endif
