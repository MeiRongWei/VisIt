/*****************************************************************************
*
* Copyright (c) 2000 - 2012, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

#ifndef MOVIEATTRIBUTES_H
#define MOVIEATTRIBUTES_H
#include <state_exports.h>
#include <string>
#include <AttributeSubject.h>


// ****************************************************************************
// Class: MovieAttributes
//
// Purpose:
//    This class contains the attributes used for saving movies.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class STATE_API MovieAttributes : public AttributeSubject
{
public:
    enum MovieTypeEnum
    {
        Simple,
        UsingTemplate
    };
    enum GenerationMethodEnum
    {
        NowCurrentInstance,
        NowNewInstance,
        Later
    };

    // These constructors are for objects of this class
    MovieAttributes();
    MovieAttributes(const MovieAttributes &obj);
protected:
    // These constructors are for objects derived from this class
    MovieAttributes(private_tmfs_t tmfs);
    MovieAttributes(const MovieAttributes &obj, private_tmfs_t tmfs);
public:
    virtual ~MovieAttributes();

    virtual MovieAttributes& operator = (const MovieAttributes &obj);
    virtual bool operator == (const MovieAttributes &obj) const;
    virtual bool operator != (const MovieAttributes &obj) const;
private:
    void Init();
    void Copy(const MovieAttributes &obj);
public:

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectOutputDirectory();
    void SelectOutputName();
    void SelectFileFormats();
    void SelectUseCurrentSize();
    void SelectWidths();
    void SelectHeights();
    void SelectScales();
    void SelectStereoFlags();
    void SelectTemplateFile();
    void SelectEmailAddress();

    // Property setting methods
    void SetGenerationMethod(GenerationMethodEnum generationMethod_);
    void SetMovieType(MovieTypeEnum movieType_);
    void SetOutputDirectory(const std::string &outputDirectory_);
    void SetOutputName(const std::string &outputName_);
    void SetFileFormats(const stringVector &fileFormats_);
    void SetUseCurrentSize(const unsignedCharVector &useCurrentSize_);
    void SetWidths(const intVector &widths_);
    void SetHeights(const intVector &heights_);
    void SetScales(const doubleVector &scales_);
    void SetStereoFlags(const intVector &stereoFlags_);
    void SetTemplateFile(const std::string &templateFile_);
    void SetSendEmailNotification(bool sendEmailNotification_);
    void SetUseScreenCapture(bool useScreenCapture_);
    void SetEmailAddress(const std::string &emailAddress_);
    void SetFps(int fps_);
    void SetStartIndex(int startIndex_);
    void SetEndIndex(int endIndex_);
    void SetStride(int stride_);

    // Property getting methods
    GenerationMethodEnum     GetGenerationMethod() const;
    MovieTypeEnum            GetMovieType() const;
    const std::string        &GetOutputDirectory() const;
          std::string        &GetOutputDirectory();
    const std::string        &GetOutputName() const;
          std::string        &GetOutputName();
    const stringVector       &GetFileFormats() const;
          stringVector       &GetFileFormats();
    const unsignedCharVector &GetUseCurrentSize() const;
          unsignedCharVector &GetUseCurrentSize();
    const intVector          &GetWidths() const;
          intVector          &GetWidths();
    const intVector          &GetHeights() const;
          intVector          &GetHeights();
    const doubleVector       &GetScales() const;
          doubleVector       &GetScales();
    const intVector          &GetStereoFlags() const;
          intVector          &GetStereoFlags();
    const std::string        &GetTemplateFile() const;
          std::string        &GetTemplateFile();
    bool                     GetSendEmailNotification() const;
    bool                     GetUseScreenCapture() const;
    const std::string        &GetEmailAddress() const;
          std::string        &GetEmailAddress();
    int                      GetFps() const;
    int                      GetStartIndex() const;
    int                      GetEndIndex() const;
    int                      GetStride() const;

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);

    // Enum conversion functions
    static std::string MovieTypeEnum_ToString(MovieTypeEnum);
    static bool MovieTypeEnum_FromString(const std::string &, MovieTypeEnum &);
protected:
    static std::string MovieTypeEnum_ToString(int);
public:
    static std::string GenerationMethodEnum_ToString(GenerationMethodEnum);
    static bool GenerationMethodEnum_FromString(const std::string &, GenerationMethodEnum &);
protected:
    static std::string GenerationMethodEnum_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

    // User-defined methods
    void ValidateFormats(DataNode *);

    // IDs that can be used to identify fields in case statements
    enum {
        ID_generationMethod = 0,
        ID_movieType,
        ID_outputDirectory,
        ID_outputName,
        ID_fileFormats,
        ID_useCurrentSize,
        ID_widths,
        ID_heights,
        ID_scales,
        ID_stereoFlags,
        ID_templateFile,
        ID_sendEmailNotification,
        ID_useScreenCapture,
        ID_emailAddress,
        ID_fps,
        ID_startIndex,
        ID_endIndex,
        ID_stride,
        ID__LAST
    };

private:
    int                generationMethod;
    int                movieType;
    std::string        outputDirectory;
    std::string        outputName;
    stringVector       fileFormats;
    unsignedCharVector useCurrentSize;
    intVector          widths;
    intVector          heights;
    doubleVector       scales;
    intVector          stereoFlags;
    std::string        templateFile;
    bool               sendEmailNotification;
    bool               useScreenCapture;
    std::string        emailAddress;
    int                fps;
    int                startIndex;
    int                endIndex;
    int                stride;

    // Static class format string for type map.
    static const char *TypeMapFormatString;
    static const private_tmfs_t TmfsStruct;
};
#define MOVIEATTRIBUTES_TMFS "iisss*u*i*i*d*i*sbbsiiii"

#endif
