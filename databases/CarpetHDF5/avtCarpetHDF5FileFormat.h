/*****************************************************************************
*
* Copyright (c) 2000 - 2012, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* All rights reserved.
*
* This file is part of VisIt. For details, see http://www.llnl.gov/visit/. The
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
*    documentation and/or materials provided with the distribution.
*  - Neither the name of the UC/LLNL nor  the names of its contributors may be
*    used to  endorse or  promote products derived from  this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED.  IN  NO  EVENT  SHALL  THE  REGENTS  OF  THE  UNIVERSITY OF
* CALIFORNIA, THE U.S.  DEPARTMENT  OF  ENERGY OR CONTRIBUTORS BE  LIABLE  FOR
* ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//                            avtCarpetHDF5FileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_CarpetHDF5_FILE_FORMAT_H
#define AVT_CarpetHDF5_FILE_FORMAT_H

#include <avtMTMDFileFormat.h>
#include <avtSpatialBoxSelection.h>

#include <hdf5.h>

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>

// ****************************************************************************
//  Class: avtCarpetHDF5FileFormat
//
//  Purpose:
//      Reads in CarpetHDF5 files as a plugin to VisIt.
//
//  Programmer: Christian Reisswig -- generated by xml2avt
//  Creation:   Tue Jan 22 15:54:40 PST 2008
//
// ****************************************************************************

/**
   One dataset_entry comprises one local patch (component) of a Carpet-map
*/
class dataset_entry
{
   public :
            dataset_entry() : _name(""), _cycle(-1), _time(-1), _file_id(-1), _ndims(-1) { }
            dataset_entry(const std::string& name_,
                          const std::string& varname_,
                          const int cycle_, 
                          const double time_,
                          const int rl_,
                          const int map_,
                          const int factor_,
                          const int type_,
                          const int comps_,
                          const std::vector<double>& origin_,
                          const std::vector<double>& delta_,
                          const std::vector<int>& iorigin_,
                          const int ndims_,
                          const std::vector<hsize_t>& dims_,
                          const bool is_Cartesian_,
                          const std::vector<int>& ghosts_)
               : _name(name_), _varname(varname_), _cycle(cycle_), _time(time_), _file_id(-1), _origin(origin_), _origin_ghosted(origin_),
                 _iorigin(iorigin_), _iorigin_ghosted(iorigin_), _delta(delta_), _rl(rl_), _map(map_), 
                 _factor(factor_), _type(type_), _comps(comps_), _ndims(ndims_), _dims(dims_), _dims_ghosted(dims_), _is_Cartesian(is_Cartesian_),
                 _range(0), _blanks(0), _npoints(std::vector<int>(ndims_, 0)), _npoints_ghosted(std::vector<int>(ndims_, 0)), _ghosts(ghosts_),
                 _isOutermostX(false), _isOutermostY(false), _isOutermostZ(false), _isLowerOutermostX(false), _isLowerOutermostY(false), _isLowerOutermostZ(false)
            {     
                // put hdf5's c-ordering in correct order
                for (int d=0; d < _ndims; d++)
                    _npoints[d] = _dims[_ndims-1-d];
                                
                // set nominal domain size
                for (int d=0; d < _ndims; d++)
                {
                    if (_ghosts[2*d] > 0 || _ghosts[2*d+1] > 0)
                       _npoints_ghosted[d] = _npoints[d] - _ghosts[2*d] - _ghosts[2*d+1] + 1;  // addaing a "1" assumes that we have a ghostzone from which we can take it!
                    else
                       _npoints_ghosted[d] = _npoints[d];
                    _iorigin_ghosted[d] = _iorigin[d] + _ghosts[2*d];
                    _origin_ghosted[d] = _origin[d] + _ghosts[2*d] * _delta[d];
                    
                    if (_ghosts[2*d] > 0 || _ghosts[2*d+1] > 0)
                    {
                       if (_rl > 0 && _iorigin_ghosted[d] % int(pow((double)2, 1)) >  0) { _npoints_ghosted[d] += 1; _iorigin_ghosted[d] -= 1; _origin_ghosted[d] -= _delta[d]; _ghosts[2*d] -= 1; }
                       if (_rl > 0 && _npoints_ghosted[d] % int(pow((double)2, 1)) == 0) { _npoints_ghosted[d] -= 1; /*_ghosts[2*d+1 += 1;*/ }
                    }
                }
                
                // translate into hdf5's c-ordering
                for (int d=0; d < _ndims; d++)
                    _dims_ghosted[d] = _npoints_ghosted[_ndims-1-d];
            }
            dataset_entry(const char* name_,
                          const char* varname_,
                          const int cycle_, 
                          const double time_,
                          const int rl_,
                          const int map_,
                          const int factor_,
                          const int type_,
                          const int comps_,
                          const double* origin_,
                          const double* delta_,
                          const int* iorigin_,
                          const int ndims_,
                          const hsize_t* dims_,
                          const bool is_Cartesian_,
                          const int* ghosts_)
               : _name(name_), _varname(varname_), _cycle(cycle_), _time(time_), _file_id(-1), _origin(origin_, origin_+ndims_), _origin_ghosted(origin_, origin_+ndims_),
                 _iorigin(iorigin_, iorigin_+ndims_), _iorigin_ghosted(iorigin_, iorigin_+ndims_), _delta(delta_, delta_+ndims_), _rl(rl_), _map(map_), 
                 _factor(factor_), _type(type_), _comps(comps_), _ndims(ndims_), _dims(dims_,dims_+ndims_), _dims_ghosted(dims_, dims_+ndims_), _is_Cartesian(is_Cartesian_),
                 _range(0), _blanks(0), _npoints(ndims_, 0), _npoints_ghosted(ndims_, 0), _ghosts(ghosts_, ghosts_+2*ndims_),
                 _isOutermostX(false), _isOutermostY(false), _isOutermostZ(false), _isLowerOutermostX(false), _isLowerOutermostY(false), _isLowerOutermostZ(false)
            {                
                // put hdf5's c-ordering in correct order
                for (int d=0; d < _ndims; d++)
                    _npoints[d] = _dims[_ndims-1-d];
                                
                // set nominal domain size
                for (int d=0; d < _ndims; d++)
                {
                    if (_ghosts[2*d] > 0 || _ghosts[2*d+1] > 0)
                       _npoints_ghosted[d] = _npoints[d] - _ghosts[2*d] - _ghosts[2*d+1] + 1;  // addaing a "1" assumes that we have a ghostzone from which we can take it!
                    else
                       _npoints_ghosted[d] = _npoints[d];
                    _iorigin_ghosted[d] = _iorigin[d] + _ghosts[2*d];
                    _origin_ghosted[d] = _origin[d] + _ghosts[2*d] * _delta[d];
                    
                    if (_ghosts[2*d] > 0 || _ghosts[2*d+1] > 0)
                    {
                       if (_rl > 0 && _iorigin_ghosted[d] % int(pow((double)2, 1)) >  0) { _npoints_ghosted[d] += 1; _iorigin_ghosted[d] -= 1; _origin_ghosted[d] -= _delta[d]; _ghosts[2*d] -= 1; }
                       if (_rl > 0 && _npoints_ghosted[d] % int(pow((double)2, 1)) == 0) { _npoints_ghosted[d] -= 1; /*_ghosts[2*d+1 += 1;*/ }
                    }
                }
                
                // translate into hdf5's c-ordering
                for (int d=0; d < _ndims; d++)
                    _dims_ghosted[d] = _npoints_ghosted[_ndims-1-d];
            }
            
            virtual ~dataset_entry() { }
            
            bool operator<(const dataset_entry& d) const 
            { 
               if (_cycle == d._cycle)
                  return (_rl < d._rl);
               else
                  return (_cycle < d._cycle); 
            }
            
            std::string name()    const { return _name; }
            std::string varname() const { return _varname; }
            int    cycle()   const { return _cycle; }
            double time()    const { return _time; }
            int    file_id() const { return _file_id; }
            int    map()     const { return _map; }
            int    rl()      const { return _rl; }
            int&   factor()        { return _factor; }
            bool   is_Cartesian() const { return _is_Cartesian; }
            int    type() const { return _type; }
            int    comps() const { return _comps; }
            int    ndims() const { return _ndims; }
            std::vector<hsize_t> dims(const bool removeGhosts=true) const { return removeGhosts ? _dims_ghosted : _dims; }
            std::vector<int>     npoints(const bool removeGhosts=true) const { return removeGhosts ? _npoints_ghosted :_npoints; }
            std::vector<double>  origin(const bool removeGhosts=true) const { return removeGhosts ? _origin_ghosted :_origin; }
            std::vector<double>  delta() const { return _delta; }
            std::vector<int>     iorigin(const bool removeGhosts=true) const { return removeGhosts ? _iorigin_ghosted : _iorigin; }
            std::vector<int>     ghosts(const bool removeGhosts=true) const { return removeGhosts ? _ghosts : std::vector<int>(_ndims*2, 0); } // must returns 0 ghosts if removeGhosts==false
            
            std::vector<int>& range() { return _range; }
            std::vector<int>& blanks() { return _blanks; }
            
            void set_file_id( const int file_id_) { _file_id = file_id_; };
            
            // This routine must be called when a timestp is constructed.
            // This is because the domain needs to know whether it is at a true external (reflevel) boundary
            // or an internal boundary between patches of the same reflevel.
            void setOutermost(const bool isOutermostX_, const bool isOutermostY_, const bool isOutermostZ_)
            {
                _isOutermostX = isOutermostX_;
                _isOutermostY = isOutermostY_;
                _isOutermostZ = isOutermostZ_;
                
                // Enlarge domain by one point so that we get connectivity information.
                // However, we can only do that, if we have ghostzones!
                /*if (!_isOutermostX && _ghosts[1] > 0) _npoints_ghosted[0] += 1;
                if (!_isOutermostY && _ghosts[3] > 0) _npoints_ghosted[1] += 1;
                if (!_isOutermostZ && _ghosts[5] > 0) _npoints_ghosted[2] += 1;
                
                // For proper AMR nesting, we need to make sure that we have an odd
                // number of points for finer patches. Otherwise we cover only half of the coarser cell
                // at the boundary
                if (_rl > 0 && _isOutermostX && (_npoints_ghosted[0]+_iorigin[0]) % 2 == 1) _npoints_ghosted[0] -= 1;
                if (_rl > 0 && _isOutermostY && (_npoints_ghosted[1]+_iorigin[1]) % 2 == 1) _npoints_ghosted[1] -= 1;
                if (_rl > 0 && _isOutermostZ && (_npoints_ghosted[2]+_iorigin[2]) % 2 == 1) _npoints_ghosted[2] -= 1;
                
                // translate into hdf5's c-ordering
                for (int d=0; d < _ndims; d++)
                    _dims_ghosted[d] = _npoints_ghosted[_ndims-1-d];*/
            }
            
            // This routine must be called when a timestp is constructed.
            // This is because the domain needs to know whether it is at a true external (reflevel) boundary
            // or an internal boundary between patches of the same reflevel.
            void setLowerOutermost(const bool isLowerOutermostX_, const bool isLowerOutermostY_, const bool isLowerOutermostZ_)
            {
                _isLowerOutermostX = isLowerOutermostX_;
                _isLowerOutermostY = isLowerOutermostY_;
                _isLowerOutermostZ = isLowerOutermostZ_;
                
                // Enlarge domain by one point so that we get connectivity information.
                // However, we can only do that, if we have ghostzones!
                /*if (!_isLowerOutermostX && _ghosts[0] > 0) _npoints_ghosted[0] += 1;
                if (!_isLowerOutermostY && _ghosts[2] > 0) _npoints_ghosted[1] += 1;
                if (!_isLowerOutermostZ && _ghosts[4] > 0) _npoints_ghosted[2] += 1;
                
                // For proper AMR nesting, we need to make sure that we have an odd
                // number of points for finer patches. Otherwise we cover only half of the coarser cell
                // at the boundary
                if (_rl > 0 && _isLowerOutermostX && (_iorigin_ghosted[0]) % 2 == 1) { _npoints_ghosted[0] -= 1; _iorigin_ghosted -=1; }
                if (_rl > 0 && _isLowerOutermostY && (_iorigin_ghosted[1]) % 2 == 1) _npoints_ghosted[1] -= 1;
                if (_rl > 0 && _isLowerOutermostZ && (_iorigin_ghosted[2]) % 2 == 1) _npoints_ghosted[2] -= 1;
                
                // translate into hdf5's c-ordering
                for (int d=0; d < _ndims; d++)
                    _dims_ghosted[d] = _npoints_ghosted[_ndims-1-d];*/
            }
            
            double xmin() const { return origin()[0]; }
            double ymin() const { return origin()[1]; }
            double zmin() const { return origin()[2]; }
            double xmax() const { return origin()[0] +  (npoints()[0]-1) * delta()[0]; }
            double ymax() const { return origin()[1] +  (npoints()[1]-1) * delta()[1]; }
            double zmax() const { return origin()[2] +  (npoints()[2]-1) * delta()[2]; }
            
            // checks whether given component shares a boundary with the boundary of the total domain
            // on the given reflevel.
            bool is_at_upper_total_rl_domain_boundary(const int dir, const int outerBoundaryLoc) const
            {
               return (npoints(false)[dir]+iorigin(false)[dir] >= outerBoundaryLoc);
            }
            
            // checks whether given component shares a boundary with the boundary of the total domain
            // on the given reflevel.
            bool is_at_lower_total_rl_domain_boundary(const int dir, const int lowerBoundaryLoc) const
            {
               return (iorigin(false)[dir] <= lowerBoundaryLoc);
            }
            
   private :
            std::string _name;     // name of the dataset
            std::string _varname;  // name of the variable
            int    _cycle;    // cycle of the dataset
            double _time;     // time of the dataset
            int    _file_id;  // the file number from which this dataset-entry was obtained
            int    _rl;       // refinement level
            int    _map;      // map number
            int    _factor;   // refinement factor
            int    _type;     // type of variable (0 = real, 1 = complex, 2 = vector)
            int    _comps;    // number of vector components  
            int    _ndims;    // number of dimensions
            
            std::vector<hsize_t> _dims;          // the grid size in each direction --- this (as opposed to all other arrays below) is in C-order, i.e. [0] = z, [1] = y, [2] = x
            std::vector<int>     _npoints;       // the grid size in each direction, but in correct order!
            std::vector<double>  _origin;        // coordinate origin of point (i=0,j=0,k=0)
            std::vector<double>  _delta;         // grid delta-spacing
            std::vector<int>     _iorigin;       // grid indices of patch location (in the index-space of the current reflevel)
            
            // the same as above but with ghostzones removed
            std::vector<hsize_t> _dims_ghosted; 
            std::vector<int>     _npoints_ghosted;
            std::vector<double>  _origin_ghosted;
            std::vector<int>     _iorigin_ghosted;
            
            std::vector<int> _ghosts;  // ghostzone-width on lower and upper bound 3per direction (dim = 2*ndims)
            
            std::vector<int> _range;
            std::vector<int> _blanks;         // blanked-out ghost-cells
            
            bool _is_Cartesian;           // if this is the central Cartesian patch then treat it differently
            bool _isOutermostX;           // is this component one of the outermosts in x-idrection on the current reflevel?
            bool _isOutermostY;
            bool _isOutermostZ;
            
            bool _isLowerOutermostX;           // is this component one of the lower outermosts in -x-idrection on the current reflevel?
            bool _isLowerOutermostY;
            bool _isLowerOutermostZ;
};


class timestep_t
{
   public :
            timestep_t() : max_cart_rl(0), max_multi_rl(0), totalCartDomainExt(std::vector<std::vector<double> >(0)), totalCartDomainIExt(std::vector<std::vector<int> >(0)) { }
            timestep_t &operator=(std::vector<std::vector<const dataset_entry*> >& dsets)
            {
               cart_comp.resize(dsets.size());
               multi_comp.resize(dsets.size());
               
               for (int v=0; v < dsets.size(); v++)
               {
                  for (int i=0; i < dsets[v].size(); i++)
                  {
                     if (dsets[v][i]->is_Cartesian())
                     {
                        cart_comp[v].push_back(*dsets[v][i]);
                        if (dsets[v][i]->rl()+1 > max_cart_rl)
                           max_cart_rl = dsets[v][i]->rl()+1;
                     }
                     else
                     {
                        multi_comp[v].push_back(*dsets[v][i]);
                        if (dsets[v][i]->rl()+1 > max_multi_rl)
                           max_multi_rl = dsets[v][i]->rl()+1;
                     }
                  }
                  sort(cart_comp[v].begin(), cart_comp[v].end());
                  sort(multi_comp[v].begin(), multi_comp[v].end());
               }
               
               // initialize domain extents with unrealistic values
               totalCartDomainExt = std::vector<std::vector<double> >(max_cart_rl, std::vector<double>(6, 1e20));
               totalCartDomainIExt = std::vector<std::vector<int> >(max_cart_rl, std::vector<int>(6, 1e8));
               for (int i=0; i < max_cart_rl; ++i)
               {
                  totalCartDomainExt[i][1] = -1e20;
                  totalCartDomainExt[i][3] = -1e20;
                  totalCartDomainExt[i][5] = -1e20;
                  
                  totalCartDomainIExt[i][1] = -1e8;
                  totalCartDomainIExt[i][3] = -1e8;
                  totalCartDomainIExt[i][5] = -1e8;
               }
               
               for (int i=0; i < cart_comp[0].size(); i++)
               {
                  // set refinement factor
                  cart_comp[0][i].factor() = 1 << (max_cart_rl-1 - cart_comp[0][i].rl());
                  // find domain extends
                  const int rl = cart_comp[0][i].rl();
                  if (cart_comp[0][i].xmin() < totalCartDomainExt[rl][0]) totalCartDomainExt[rl][0] = cart_comp[0][i].xmin();
                  if (cart_comp[0][i].ymin() < totalCartDomainExt[rl][2]) totalCartDomainExt[rl][2] = cart_comp[0][i].ymin();
                  if (cart_comp[0][i].zmin() < totalCartDomainExt[rl][4]) totalCartDomainExt[rl][4] = cart_comp[0][i].zmin();
                  if (cart_comp[0][i].xmax() > totalCartDomainExt[rl][1]) totalCartDomainExt[rl][1] = cart_comp[0][i].xmax();
                  if (cart_comp[0][i].ymax() > totalCartDomainExt[rl][3]) totalCartDomainExt[rl][3] = cart_comp[0][i].ymax();
                  if (cart_comp[0][i].zmax() > totalCartDomainExt[rl][5]) totalCartDomainExt[rl][5] = cart_comp[0][i].zmax();
                  // find integer domain extends
                  if (cart_comp[0][i].iorigin(false)[0] < totalCartDomainIExt[rl][0]) totalCartDomainIExt[rl][0] = cart_comp[0][i].iorigin(false)[0];
                  if (cart_comp[0][i].iorigin(false)[1] < totalCartDomainIExt[rl][2]) totalCartDomainIExt[rl][2] = cart_comp[0][i].iorigin(false)[1];
                  if (cart_comp[0][i].iorigin(false)[2] < totalCartDomainIExt[rl][4]) totalCartDomainIExt[rl][4] = cart_comp[0][i].iorigin(false)[2];
                  
                  if (cart_comp[0][i].iorigin(false)[0]+cart_comp[0][i].npoints(false)[0] > totalCartDomainIExt[rl][1]) totalCartDomainIExt[rl][1] = cart_comp[0][i].iorigin(false)[0]+cart_comp[0][i].npoints(false)[0];
                  if (cart_comp[0][i].iorigin(false)[1]+cart_comp[0][i].npoints(false)[1] > totalCartDomainIExt[rl][3]) totalCartDomainIExt[rl][3] = cart_comp[0][i].iorigin(false)[1]+cart_comp[0][i].npoints(false)[1];
                  if (cart_comp[0][i].iorigin(false)[2]+cart_comp[0][i].npoints(false)[2] > totalCartDomainIExt[rl][5]) totalCartDomainIExt[rl][5] = cart_comp[0][i].iorigin(false)[2]+cart_comp[0][i].npoints(false)[2];
                  
               }
               // set boundary info for individual Cartesian components
               for (int j=0; j < cart_comp.size(); j++)
                  for (int i=0; i < cart_comp[j].size(); i++)
                  {
                     cart_comp[j][i].setOutermost(cart_comp[j][i].is_at_upper_total_rl_domain_boundary(0, totalCartDomainIExt[cart_comp[j][i].rl()][1]),
                                                  cart_comp[j][i].is_at_upper_total_rl_domain_boundary(1, totalCartDomainIExt[cart_comp[j][i].rl()][3]),
                                                  cart_comp[j][i].is_at_upper_total_rl_domain_boundary(2, totalCartDomainIExt[cart_comp[j][i].rl()][5]));
                     cart_comp[j][i].setLowerOutermost(cart_comp[j][i].is_at_lower_total_rl_domain_boundary(0, totalCartDomainIExt[cart_comp[j][i].rl()][0]),
                                                       cart_comp[j][i].is_at_lower_total_rl_domain_boundary(1, totalCartDomainIExt[cart_comp[j][i].rl()][2]),
                                                       cart_comp[j][i].is_at_lower_total_rl_domain_boundary(2, totalCartDomainIExt[cart_comp[j][i].rl()][4]));
                  }
               for (int i=0; i < multi_comp[0].size(); i++)
               {
                  // set refinement factor
                  multi_comp[0][i].factor() = 1 << (max_multi_rl-1 - multi_comp[0][i].rl());
               }

               return *this;
            }
            
            virtual ~timestep_t() { }
            
            
            
            // allocate memory for blanked out ghostcells
            void set_ranges();
            
            // ... and the same for multi-patches
            void set_ranges_multi();
            
            // get rid auf blanked out ghostcells
            void unset_ranges() 
            { 
               for (int i=0; i < cart_comp[0].size(); i++)
               {
                  cart_comp[0][i].blanks().resize(0); 
                  cart_comp[0][i].range().resize(0);
               }
               for (int i=0; i < multi_comp[0].size(); i++)
               {
                  multi_comp[0][i].blanks().resize(0); 
                  multi_comp[0][i].range().resize(0);
               }
            }
            
            // Carpet components per reflevel per map 
            std::vector<std::vector<dataset_entry> > cart_comp;   // the Cartesian AMR mesh data-entry per component per variable
            std::vector<std::vector<dataset_entry> > multi_comp;  // the unstructured multi-patch mesh data-entry per component per variable
            
            // domain extends of the Cartesian grid per reflevel per direction
            std::vector<std::vector<double> > totalCartDomainExt;
            // domain extends in gridpoints
            std::vector<std::vector<int> > totalCartDomainIExt;
            
            int max_cart_rl;
            int max_multi_rl;
};


class avtCarpetHDF5FileFormat : public avtMTMDFileFormat
{
  private:
            // forbid copying due to pointer usage
            avtCarpetHDF5FileFormat(const avtCarpetHDF5FileFormat& format);
            avtCarpetHDF5FileFormat& operator=(const avtCarpetHDF5FileFormat& format);
  public:
    
    
    class file_t
    {
      private:
               // forbid copying
               file_t(const file_t& file);
               file_t& operator=(const file_t& file);
      public:
               hid_t file;
               
               file_t(const char* fname) : filename(fname) { file = -1; openfile(fname); }
               virtual ~file_t() { if (file >= 0) H5Fclose(file); }
               
               // open file and opbtain all datasetnames contained in that file
               void openfile(const char* fname);
               
               // filter out the available coordinates and variables given a set of varnames
               // and put them to there associated time-slot in the hierarchy and variables vector
               void set_varnames(const std::vector<std::string>& v, const std::vector<int>& cycles);
               
               // read in the data from HDF5
               void get_data(const dataset_entry& dset, float** data, const bool removeGhosts=true);
               
               // read in complex data from HDF5
               void get_complex_data(const dataset_entry& dset, float*** data, const bool removeGhosts=true);

               // are we out of date?
               bool file_changed_on_disk();
               
               std::vector<std::string>                 varnames;    // the variable names
               std::vector<dataset_entry>          dsetnames;   // datasetnames contained only in this file

               // Each file keeps track of the modification times of its
               // constituent files and avtFileFormat uses this information ot
               // invalidate a cache entry when the files change on disk
               std::string                         filename;    // name of the hdf5 file we represent
               time_t                         mtime;       // modification time when we were last opened
               time_t                         idx_mtime;   // modification time when index was last
               
    };
  
    avtCarpetHDF5FileFormat(const char *);
    virtual ~avtCarpetHDF5FileFormat()
    {
      close_cached_file(data_file);
      close_cached_file(xcoord_file);
      close_cached_file(ycoord_file);
      close_cached_file(zcoord_file);
    };

    //
    // This is used to return unconvention data -- ranging from material
    // information to information about block connectivity.
    //
     virtual void      *GetAuxiliaryData(const char *var, int timestep, 
                                         int domain, const char *type, void *args, 
                                         DestructorFunction &);
    
    /// provide AMR info to the visit cache
    virtual void           BuildDomainAuxiliaryInfo(int timeState);

    //
    // If you know the times and cycle numbers, overload this function.
    // Otherwise, VisIt will make up some reasonable ones for you.
    //
    virtual void        GetCycles(std::vector<int> &c) { c = data_file->cycles; }
    virtual void        GetTimes(std::vector<double> &t) { t = data_file->times; }
    //

    virtual int            GetNTimesteps(void);

    virtual const char    *GetType(void)   { return "CarpetHDF5"; };
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, int, const char *);
    virtual vtkDataArray  *GetVar(int, int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, int, const char *);

#ifdef USE_SELECTIONS
    virtual void           RegisterDataSelections(
                               const std::vector<avtDataSelection_p> &selList,
                               std::vector<bool> *selectionsApplied);
#endif

    // MetaData has to be read in for each new timestate
    virtual bool HasInvariantMetaData(void) const { return false; };
    virtual bool HasInvariantSIL(void) const { return false; };

    static const int dim = 3;

  protected:
    // DATA MEMBERS

    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *, int);
  
  private:
    
#ifdef USE_SELECTIONS
    void ProcessDataSelections();
#endif

    void open_all_files(const char* fname);
    class multi_file; // forward declaration
    multi_file *open_cached_file(const std::string fname);
    void close_cached_file(multi_file *file);
    
    int get_nblocks(const int timestep, const bool is_Cartesian)
    {
      if (is_Cartesian)
         return (int)data_file->timesteps[timestep].cart_comp[0].size();
      else
         return (int)data_file->timesteps[timestep].multi_comp[0].size();
    }
    
    int get_max_reflevels(const int timestep, const bool is_Cartesian)
    {
      if (is_Cartesian)
         return data_file->timesteps[timestep].max_cart_rl;
      else
         return data_file->timesteps[timestep].max_multi_rl;
    }
    
    
    
    // a multi-processor file 
    class multi_file
    {
      private:
               // forbid copying
               multi_file(const multi_file& file);
               multi_file& operator=(const multi_file& file);
      public :
               multi_file(const char* fname);
               virtual ~multi_file() 
               {
                 for(unsigned int i = 0; i < files.size(); i++) delete files[i];
               };
               
               void get_data(const bool is_Cartesian, const int timestep, const int comp, const int var_no, float** data)
               {
                  const std::vector<std::vector<dataset_entry> > &component = is_Cartesian ? timesteps[timestep].cart_comp : timesteps[timestep].multi_comp;
                  const int file_id = component[var_no][comp].file_id();
                  files[file_id]->get_data(component[var_no][comp], data);
               }
               
               void get_vector_data(const bool is_Cartesian, const int timestep, const int comp, const int var_no, float*** data)
               {
                  if (!is_Cartesian)
                  {
                     int file_id = timesteps[timestep].multi_comp[var_no][comp].file_id();
                     if (timesteps[timestep].multi_comp[var_no][comp].type() == 1)
                        files[file_id]->get_complex_data(timesteps[timestep].multi_comp[var_no][comp], data);
                     //else  -- need to implement general vector data reading here!
                  }
                  else
                  {
                     int file_id = timesteps[timestep].cart_comp[var_no][comp].file_id();
                     if (timesteps[timestep].multi_comp[var_no][comp].type() == 1)
                        files[file_id]->get_complex_data(timesteps[timestep].cart_comp[var_no][comp], data);
                     //else  -- need to implement general vector data reading here!
                  }
               }
               
               
               int            n_timesteps;
               std::vector<int>    cycles;
               std::vector<double> times;
               
               
               std::vector<timestep_t>     timesteps; // all datasets sorted by timestep
               
               std::vector<std::string>         varnames;    // the pure variable names
               
               std::vector<file_t*> files;              // the files containing the variables

               // multi_file acts as a smart pointer keeping track of how many pointers to it exist
               // creation and deletion itself are handled by avtFileFormat however
               int refcount;
    };
    
    multi_file *data_file;         // the files containing the variables
    multi_file *xcoord_file;       // the files containing the x-coordinates
    multi_file *ycoord_file;       // the files containing the y-coordinates
    multi_file *zcoord_file;       // the files containing the z-coordinates

#ifdef USE_SELECTIONS
    std::vector<avtDataSelection_p>      selections;
    std::vector<bool>                    *selectionsApplied;
#endif


    // since VisIt seeme to create and desctroy avtFileFormat
    // objects rather often and reading the metadata is expensive,
    // we cache the multifile objects.
    // Each multifile keeps track of how often it has been used (1
    // for the cache, 1 for each additional instance of file
    // opening).
    static std::map<std::string, multi_file*> file_cache;
};


#endif
