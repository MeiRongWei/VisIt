// ***************************************************************************
//
// Copyright (c) 2000 - 2008, Lawrence Livermore National Security, LLC
// Produced at the Lawrence Livermore National Laboratory
// LLNL-CODE-400142
// All rights reserved.
//
// This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
// full copyright notice is contained in the file COPYRIGHT located at the root
// of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
//
// Redistribution  and  use  in  source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
//  - Redistributions of  source code must  retain the above  copyright notice,
//    this list of conditions and the disclaimer below.
//  - Redistributions in binary form must reproduce the above copyright notice,
//    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
//    documentation and/or other materials provided with the distribution.
//  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
//    be used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
// ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
// LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
// DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
// SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
// CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
// LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
// OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ***************************************************************************

package llnl.visit;


// ****************************************************************************
// Class: Axes3D
//
// Purpose:
//    Contains the properties for the 3D axes.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   Fri Jan 25 16:52:23 PST 2008
//
// Modifications:
//   
// ****************************************************************************

public class Axes3D extends AttributeSubject
{
    // Enum values
    public final static int AXES_CLOSESTTRIAD = 0;
    public final static int AXES_FURTHESTTRIAD = 1;
    public final static int AXES_OUTSIDEEDGES = 2;
    public final static int AXES_STATICTRIAD = 3;
    public final static int AXES_STATICEDGES = 4;

    public final static int LOCATION_INSIDE = 0;
    public final static int LOCATION_OUTSIDE = 1;
    public final static int LOCATION_BOTH = 2;


    public Axes3D()
    {
        super(11);

        visible = true;
        autoSetTicks = true;
        autoSetScaling = true;
        lineWidth = 0;
        tickLocation = LOCATION_OUTSIDE;
        axesType = AXES_CLOSESTTRIAD;
        triadFlag = true;
        bboxFlag = true;
        xAxis = new AxisAttributes();
        yAxis = new AxisAttributes();
        zAxis = new AxisAttributes();
    }

    public Axes3D(Axes3D obj)
    {
        super(11);

        visible = obj.visible;
        autoSetTicks = obj.autoSetTicks;
        autoSetScaling = obj.autoSetScaling;
        lineWidth = obj.lineWidth;
        tickLocation = obj.tickLocation;
        axesType = obj.axesType;
        triadFlag = obj.triadFlag;
        bboxFlag = obj.bboxFlag;
        xAxis = new AxisAttributes(obj.xAxis);
        yAxis = new AxisAttributes(obj.yAxis);
        zAxis = new AxisAttributes(obj.zAxis);

        SelectAll();
    }

    public boolean equals(Axes3D obj)
    {
        // Create the return value
        return ((visible == obj.visible) &&
                (autoSetTicks == obj.autoSetTicks) &&
                (autoSetScaling == obj.autoSetScaling) &&
                (lineWidth == obj.lineWidth) &&
                (tickLocation == obj.tickLocation) &&
                (axesType == obj.axesType) &&
                (triadFlag == obj.triadFlag) &&
                (bboxFlag == obj.bboxFlag) &&
                (xAxis == obj.xAxis) &&
                (yAxis == obj.yAxis) &&
                (zAxis == obj.zAxis));
    }

    // Property setting methods
    public void SetVisible(boolean visible_)
    {
        visible = visible_;
        Select(0);
    }

    public void SetAutoSetTicks(boolean autoSetTicks_)
    {
        autoSetTicks = autoSetTicks_;
        Select(1);
    }

    public void SetAutoSetScaling(boolean autoSetScaling_)
    {
        autoSetScaling = autoSetScaling_;
        Select(2);
    }

    public void SetLineWidth(int lineWidth_)
    {
        lineWidth = lineWidth_;
        Select(3);
    }

    public void SetTickLocation(int tickLocation_)
    {
        tickLocation = tickLocation_;
        Select(4);
    }

    public void SetAxesType(int axesType_)
    {
        axesType = axesType_;
        Select(5);
    }

    public void SetTriadFlag(boolean triadFlag_)
    {
        triadFlag = triadFlag_;
        Select(6);
    }

    public void SetBboxFlag(boolean bboxFlag_)
    {
        bboxFlag = bboxFlag_;
        Select(7);
    }

    public void SetXAxis(AxisAttributes xAxis_)
    {
        xAxis = xAxis_;
        Select(8);
    }

    public void SetYAxis(AxisAttributes yAxis_)
    {
        yAxis = yAxis_;
        Select(9);
    }

    public void SetZAxis(AxisAttributes zAxis_)
    {
        zAxis = zAxis_;
        Select(10);
    }

    // Property getting methods
    public boolean        GetVisible() { return visible; }
    public boolean        GetAutoSetTicks() { return autoSetTicks; }
    public boolean        GetAutoSetScaling() { return autoSetScaling; }
    public int            GetLineWidth() { return lineWidth; }
    public int            GetTickLocation() { return tickLocation; }
    public int            GetAxesType() { return axesType; }
    public boolean        GetTriadFlag() { return triadFlag; }
    public boolean        GetBboxFlag() { return bboxFlag; }
    public AxisAttributes GetXAxis() { return xAxis; }
    public AxisAttributes GetYAxis() { return yAxis; }
    public AxisAttributes GetZAxis() { return zAxis; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteBool(visible);
        if(WriteSelect(1, buf))
            buf.WriteBool(autoSetTicks);
        if(WriteSelect(2, buf))
            buf.WriteBool(autoSetScaling);
        if(WriteSelect(3, buf))
            buf.WriteInt(lineWidth);
        if(WriteSelect(4, buf))
            buf.WriteInt(tickLocation);
        if(WriteSelect(5, buf))
            buf.WriteInt(axesType);
        if(WriteSelect(6, buf))
            buf.WriteBool(triadFlag);
        if(WriteSelect(7, buf))
            buf.WriteBool(bboxFlag);
        if(WriteSelect(8, buf))
            xAxis.Write(buf);
        if(WriteSelect(9, buf))
            yAxis.Write(buf);
        if(WriteSelect(10, buf))
            zAxis.Write(buf);
    }

    public void ReadAtts(int n, CommunicationBuffer buf)
    {
        for(int i = 0; i < n; ++i)
        {
            int index = (int)buf.ReadByte();
            switch(index)
            {
            case 0:
                SetVisible(buf.ReadBool());
                break;
            case 1:
                SetAutoSetTicks(buf.ReadBool());
                break;
            case 2:
                SetAutoSetScaling(buf.ReadBool());
                break;
            case 3:
                SetLineWidth(buf.ReadInt());
                break;
            case 4:
                SetTickLocation(buf.ReadInt());
                break;
            case 5:
                SetAxesType(buf.ReadInt());
                break;
            case 6:
                SetTriadFlag(buf.ReadBool());
                break;
            case 7:
                SetBboxFlag(buf.ReadBool());
                break;
            case 8:
                xAxis.Read(buf);
                Select(8);
                break;
            case 9:
                yAxis.Read(buf);
                Select(9);
                break;
            case 10:
                zAxis.Read(buf);
                Select(10);
                break;
            }
        }
    }


    // Attributes
    private boolean        visible;
    private boolean        autoSetTicks;
    private boolean        autoSetScaling;
    private int            lineWidth;
    private int            tickLocation;
    private int            axesType;
    private boolean        triadFlag;
    private boolean        bboxFlag;
    private AxisAttributes xAxis;
    private AxisAttributes yAxis;
    private AxisAttributes zAxis;
}

