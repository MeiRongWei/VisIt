// ************************************************************************* //
//                                avtViewInfo.h                              //
// ************************************************************************* //

#ifndef AVT_VIEW_INFO_H
#define AVT_VIEW_INFO_H
#include <pipeline_exports.h>

class vtkCamera;

// ****************************************************************************
//  Class: avtViewInfo
//
//  Purpose:
//    Contains all of the information for the view.
//
//  Programmer: Hank Childs
//  Creation:   November 27, 2000
//
//  Modifications:
//   Hank Childs, Wed Dec 27 14:28:01 PST 2000
//   Added viewUp.
//
//   Kathleen Bonnell, Thu Jan  4 15:40:32 PST 2001 
//   Added method to set the data members from a vtkCamera.
//
//   Kathleen Bonnell, Mon Jan  8 11:56:50 PST 2001 
//   Added method to set the data members to a vtkCamera.
//
//   Hank Childs, Mon Jun 18 09:03:19 PDT 2001
//   Added constructor.
//
//   Eric Brugger, Fri Jun  6 15:29:28 PDT 2003
//   I added image pan and image zoom.
//
//   Hank Childs, Wed Oct 15 13:09:03 PDT 2003
//   Added eye angle.
//
// ****************************************************************************

struct PIPELINE_API avtViewInfo
{
    double   camera[3];
    double   focus[3];
    double   viewUp[3];
    double   viewAngle;
    double   eyeAngle;
    double   parallelScale;
    bool     setScale;
    double   nearPlane;
    double   farPlane;
    double   imagePan[2];
    double   imageZoom;
    bool     orthographic;

  public:
                    avtViewInfo();
    avtViewInfo   & operator=(const avtViewInfo &);
    bool            operator==(const avtViewInfo &);
    void            SetToDefault(void);
    void            SetViewFromCamera(vtkCamera *);
    void            SetCameraFromView(vtkCamera *) const;
};


#endif


