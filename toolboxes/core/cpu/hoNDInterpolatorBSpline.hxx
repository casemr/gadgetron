/** \file       hoNDInterpolatorBSpline.hxx
    \brief      N-dimensional BSpline interpolator

                Designed to work with hoNDArray and hoNDImage

    \author     Hui Xue
*/

namespace Gadgetron
{
    template <typename ArrayType, unsigned int D> 
    hoNDInterpolatorBSpline<ArrayType, D>::hoNDInterpolatorBSpline(ArrayType& a, BoundHanlderType& bh, unsigned int order) : BaseClass(a, bh), order_(order)
    {
        bspline_.computeBSplineCoefficients(a, order_, this->coeff_);

        dimension_.resize(D);

        unsigned int ii;
        for ( ii=0; ii<D; ii++ )
        {
            dimension_[ii] = a.get_size(ii);
        }

        derivative_.resize(D, 0);
    }

    template <typename ArrayType, unsigned int D> 
    hoNDInterpolatorBSpline<ArrayType, D>::~hoNDInterpolatorBSpline()
    {
    }

    template <typename ArrayType, unsigned int D> 
    void hoNDInterpolatorBSpline<ArrayType, D>::setArray(ArrayType& a)
    {
        this->array_ = &a;

        dimension_.resize(D);

        unsigned int ii;
        for ( ii=0; ii<D; ii++ )
        {
            dimension_[ii] = a.get_size(ii);
        }

        bspline_.computeBSplineCoefficients(a, this->order_, this->coeff_);
    }

    template <typename ArrayType, unsigned int D> 
    inline typename hoNDInterpolatorBSpline<ArrayType, D>::T hoNDInterpolatorBSpline<ArrayType, D>::operator()( const coord_type* pos )
    {
        std::vector<gt_index_type> anchor(D);

        unsigned int ii;
        for ( ii=0; ii<D; ii++ )
        {
            anchor[ii] = static_cast<gt_index_type>(std::floor(pos[ii]));
        }

        bool inRange = true;
        for ( ii=0; ii<D; ii++ )
        {
            if ( anchor[ii]<0 || anchor[ii]>=array_->get_size(ii) )
            {
                inRange = false;
                break;
            }
        }

        if( inRange )
        {
            return bspline_.evaluateBSpline(coeff_.begin(), dimension_, order_, derivative_, pos);
        }
        else
        {
            return (*bh_)(anchor);
        }
    }

    template <typename ArrayType, unsigned int D> 
    inline typename hoNDInterpolatorBSpline<ArrayType, D>::T hoNDInterpolatorBSpline<ArrayType, D>::operator()( const std::vector<coord_type>& pos )
    {
        return this->operator()(&pos[0]);
    }

    template <typename ArrayType, unsigned int D> 
    inline typename hoNDInterpolatorBSpline<ArrayType, D>::T hoNDInterpolatorBSpline<ArrayType, D>::operator()( coord_type x )
    {
        gt_index_type ix = static_cast<gt_index_type>(std::floor(x));

        if ( ix>=0 && ix<(gt_index_type)array_->get_size(0)-1 )
        {
            return bspline_.evaluateBSpline(coeff_.begin(), dimension_[0], order_, derivative_[0], x);
        }
        else
        {
            return (*bh_)(ix);
        }
    }

    template <typename ArrayType, unsigned int D> 
    inline typename hoNDInterpolatorBSpline<ArrayType, D>::T hoNDInterpolatorBSpline<ArrayType, D>::operator()( coord_type x, coord_type y )
    {
        gt_index_type ix = static_cast<gt_index_type>(std::floor(x));
        gt_index_type iy = static_cast<gt_index_type>(std::floor(y));

        /*x = (x<0) ? 0 : x;
        x = (x>array_->get_size(0)-1) ? array_->get_size(0)-1 : x;

        y = (y<0) ? 0 : y;
        y = (y>array_->get_size(1)-1) ? array_->get_size(1)-1 : y;*/

        if ( ix>=0 && ix<(gt_index_type)array_->get_size(0)-1 && iy>=0 && iy<(gt_index_type)array_->get_size(1)-1 )
        {
            return bspline_.evaluateBSpline(coeff_.begin(), dimension_[0], dimension_[1], order_, derivative_[0], derivative_[1], x, y);
        }
        else
        {
            return (*bh_)(ix, iy);
        }
    }

    template <typename ArrayType, unsigned int D> 
    inline typename hoNDInterpolatorBSpline<ArrayType, D>::T hoNDInterpolatorBSpline<ArrayType, D>::operator()( coord_type x, coord_type y, coord_type z )
    {
        gt_index_type ix = static_cast<gt_index_type>(std::floor(x));
        gt_index_type iy = static_cast<gt_index_type>(std::floor(y));
        gt_index_type iz = static_cast<gt_index_type>(std::floor(z));

        if ( ix>=0 && ix<(gt_index_type)array_->get_size(0)-1 
            && iy>=0 && iy<(gt_index_type)array_->get_size(1)-1 
            && iz>=0 && iz<(gt_index_type)array_->get_size(2)-1 )
        {
            return bspline_.evaluateBSpline(coeff_.begin(), 
                dimension_[0], dimension_[1], dimension_[2], 
                order_, 
                derivative_[0], derivative_[1], derivative_[2], 
                x, y, z);
        }
        else
        {
            return (*bh_)(ix, iy, iz);
        }
    }

    template <typename ArrayType, unsigned int D> 
    inline typename hoNDInterpolatorBSpline<ArrayType, D>::T hoNDInterpolatorBSpline<ArrayType, D>::operator()( coord_type x, coord_type y, coord_type z, coord_type s )
    {
        gt_index_type ix = static_cast<gt_index_type>(std::floor(x));
        gt_index_type iy = static_cast<gt_index_type>(std::floor(y));
        gt_index_type iz = static_cast<gt_index_type>(std::floor(z));
        gt_index_type is = static_cast<gt_index_type>(std::floor(s));

        if ( ix>=0 && ix<(gt_index_type)array_->get_size(0)-1 
            && iy>=0 && iy<(gt_index_type)array_->get_size(1)-1 
            && iz>=0 && iz<(gt_index_type)array_->get_size(2)-1 
            && is>=0 && is<(gt_index_type)array_->get_size(3)-1 )
        {
            return bspline_.evaluateBSpline(coeff_.begin(), 
                dimension_[0], dimension_[1], dimension_[2], dimension_[3], 
                order_, 
                derivative_[0], derivative_[1], derivative_[2], derivative_[3], 
                x, y, z, s);
        }
        else
        {
            return (*bh_)(ix, iy, iz, is);
        }
    }

    template <typename ArrayType, unsigned int D> 
    inline typename hoNDInterpolatorBSpline<ArrayType, D>::T hoNDInterpolatorBSpline<ArrayType, D>::operator()( coord_type x, coord_type y, coord_type z, coord_type s, coord_type p )
    {
        gt_index_type ix = static_cast<gt_index_type>(std::floor(x));
        gt_index_type iy = static_cast<gt_index_type>(std::floor(y));
        gt_index_type iz = static_cast<gt_index_type>(std::floor(z));
        gt_index_type is = static_cast<gt_index_type>(std::floor(s));
        gt_index_type ip = static_cast<gt_index_type>(std::floor(p));

        if ( ix>=0 && ix<(gt_index_type)array_->get_size(0)-1 
            && iy>=0 && iy<(gt_index_type)array_->get_size(1)-1 
            && iz>=0 && iz<(gt_index_type)array_->get_size(2)-1 
            && is>=0 && is<(gt_index_type)array_->get_size(3)-1 
            && ip>=0 && ip<(gt_index_type)array_->get_size(4)-1 )
        {
            return bspline_.evaluateBSpline(coeff_.begin(), 
                dimension_[0], dimension_[1], dimension_[2], dimension_[3], dimension_[4], 
                order_, 
                derivative_[0], derivative_[1], derivative_[2], derivative_[3], derivative_[4], 
                x, y, z, s, p);
        }
        else
        {
            return (*bh_)(ix, iy, iz, is, ip);
        }
    }

    template <typename ArrayType, unsigned int D> 
    inline typename hoNDInterpolatorBSpline<ArrayType, D>::T hoNDInterpolatorBSpline<ArrayType, D>::operator()( coord_type x, coord_type y, coord_type z, coord_type s, coord_type p, coord_type r )
    {
        gt_index_type ix = static_cast<gt_index_type>(std::floor(x));
        gt_index_type iy = static_cast<gt_index_type>(std::floor(y));
        gt_index_type iz = static_cast<gt_index_type>(std::floor(z));
        gt_index_type is = static_cast<gt_index_type>(std::floor(s));
        gt_index_type ip = static_cast<gt_index_type>(std::floor(p));
        gt_index_type ir = static_cast<gt_index_type>(std::floor(r));

        if ( ix>=0 && ix<(gt_index_type)array_->get_size(0)-1 
            && iy>=0 && iy<(gt_index_type)array_->get_size(1)-1 
            && iz>=0 && iz<(gt_index_type)array_->get_size(2)-1 
            && is>=0 && is<(gt_index_type)array_->get_size(3)-1 
            && ip>=0 && ip<(gt_index_type)array_->get_size(4)-1 
            && ir>=0 && ir<(gt_index_type)array_->get_size(5)-1 )
        {
            return bspline_.evaluateBSpline(coeff_.begin(), 
                dimension_[0], dimension_[1], dimension_[2], dimension_[3], dimension_[4], dimension_[5], 
                order_, 
                derivative_[0], derivative_[1], derivative_[2], derivative_[3], derivative_[4], derivative_[5], 
                x, y, z, s, p, r);
        }
        else
        {
            return (*bh_)(ix, iy, iz, is, ip, ir);
        }
    }

    template <typename ArrayType, unsigned int D> 
    inline typename hoNDInterpolatorBSpline<ArrayType, D>::T hoNDInterpolatorBSpline<ArrayType, D>::operator()( coord_type x, coord_type y, coord_type z, coord_type s, coord_type p, coord_type r, coord_type a )
    {
        gt_index_type anchor[7];

        anchor[0] = static_cast<gt_index_type>(std::floor(x));
        anchor[1] = static_cast<gt_index_type>(std::floor(y));
        anchor[2] = static_cast<gt_index_type>(std::floor(z));
        anchor[3] = static_cast<gt_index_type>(std::floor(s));
        anchor[4] = static_cast<gt_index_type>(std::floor(p));
        anchor[5] = static_cast<gt_index_type>(std::floor(r));
        anchor[6] = static_cast<gt_index_type>(std::floor(a));

        if ( anchor[0]>=0 && anchor[0]<(gt_index_type)array_->get_size(0)-1 
            && anchor[1]>=0 && anchor[1]<(gt_index_type)array_->get_size(1)-1 
            && anchor[2]>=0 && anchor[2]<(gt_index_type)array_->get_size(2)-1 
            && anchor[3]>=0 && anchor[3]<(gt_index_type)array_->get_size(3)-1 
            && anchor[4]>=0 && anchor[4]<(gt_index_type)array_->get_size(4)-1 
            && anchor[5]>=0 && anchor[5]<(gt_index_type)array_->get_size(5)-1
            && anchor[6]>=0 && anchor[6]<(gt_index_type)array_->get_size(6)-1 )
        {
            return bspline_.evaluateBSpline(coeff_.begin(), 
                dimension_[0], dimension_[1], dimension_[2], dimension_[3], dimension_[4], dimension_[5], dimension_[6], 
                order_, 
                derivative_[0], derivative_[1], derivative_[2], derivative_[3], derivative_[4], derivative_[5], derivative_[6], 
                x, y, z, s, p, r, a);
        }
        else
        {
            return (*bh_)(anchor[0], anchor[1], anchor[1], anchor[2], anchor[3], anchor[4], anchor[5], anchor[6]);
        }
    }

    template <typename ArrayType, unsigned int D> 
    inline typename hoNDInterpolatorBSpline<ArrayType, D>::T hoNDInterpolatorBSpline<ArrayType, D>::operator()( coord_type x, coord_type y, coord_type z, coord_type s, coord_type p, coord_type r, coord_type a, coord_type q )
    {
        gt_index_type anchor[8];

        anchor[0] = static_cast<gt_index_type>(std::floor(x));
        anchor[1] = static_cast<gt_index_type>(std::floor(y));
        anchor[2] = static_cast<gt_index_type>(std::floor(z));
        anchor[3] = static_cast<gt_index_type>(std::floor(s));
        anchor[4] = static_cast<gt_index_type>(std::floor(p));
        anchor[5] = static_cast<gt_index_type>(std::floor(r));
        anchor[6] = static_cast<gt_index_type>(std::floor(a));
        anchor[7] = static_cast<gt_index_type>(std::floor(q));

        if ( anchor[0]>=0 && anchor[0]<(gt_index_type)array_->get_size(0)-1 
            && anchor[1]>=0 && anchor[1]<(gt_index_type)array_->get_size(1)-1 
            && anchor[2]>=0 && anchor[2]<(gt_index_type)array_->get_size(2)-1 
            && anchor[3]>=0 && anchor[3]<(gt_index_type)array_->get_size(3)-1 
            && anchor[4]>=0 && anchor[4]<(gt_index_type)array_->get_size(4)-1 
            && anchor[5]>=0 && anchor[5]<(gt_index_type)array_->get_size(5)-1 
            && anchor[6]>=0 && anchor[6]<(gt_index_type)array_->get_size(6)-1 
            && anchor[7]>=0 && anchor[7]<(gt_index_type)array_->get_size(7)-1 )
        {
            return bspline_.evaluateBSpline(coeff_.begin(), 
                dimension_[0], dimension_[1], dimension_[2], dimension_[3], dimension_[4], dimension_[5], dimension_[6], dimension_[7], 
                order_, 
                derivative_[0], derivative_[1], derivative_[2], derivative_[3], derivative_[4], derivative_[5], derivative_[6], derivative_[7], 
                x, y, z, s, p, r, a, q);
        }
        else
        {
            return (*bh_)(anchor[0], anchor[1], anchor[1], anchor[2], anchor[3], anchor[4], anchor[5], anchor[6], anchor[7]);
        }
    }

    template <typename ArrayType, unsigned int D> 
    inline typename hoNDInterpolatorBSpline<ArrayType, D>::T hoNDInterpolatorBSpline<ArrayType, D>::operator()( coord_type x, coord_type y, coord_type z, coord_type s, coord_type p, coord_type r, coord_type a, coord_type q, coord_type u )
    {
        gt_index_type anchor[9];

        anchor[0] = static_cast<gt_index_type>(std::floor(x));
        anchor[1] = static_cast<gt_index_type>(std::floor(y));
        anchor[2] = static_cast<gt_index_type>(std::floor(z));
        anchor[3] = static_cast<gt_index_type>(std::floor(s));
        anchor[4] = static_cast<gt_index_type>(std::floor(p));
        anchor[5] = static_cast<gt_index_type>(std::floor(r));
        anchor[6] = static_cast<gt_index_type>(std::floor(a));
        anchor[7] = static_cast<gt_index_type>(std::floor(q));
        anchor[8] = static_cast<gt_index_type>(std::floor(u));

        if ( anchor[0]>=0 && anchor[0]<(gt_index_type)array_->get_size(0)-1 
            && anchor[1]>=0 && anchor[1]<(gt_index_type)array_->get_size(1)-1 
            && anchor[2]>=0 && anchor[2]<(gt_index_type)array_->get_size(2)-1 
            && anchor[3]>=0 && anchor[3]<(gt_index_type)array_->get_size(3)-1 
            && anchor[4]>=0 && anchor[4]<(gt_index_type)array_->get_size(4)-1 
            && anchor[5]>=0 && anchor[5]<(gt_index_type)array_->get_size(5)-1 
            && anchor[6]>=0 && anchor[6]<(gt_index_type)array_->get_size(6)-1 
            && anchor[7]>=0 && anchor[7]<(gt_index_type)array_->get_size(7)-1 
            && anchor[8]>=0 && anchor[8]<(gt_index_type)array_->get_size(8)-1 )
        {
            return bspline_.evaluateBSpline(coeff_.begin(), 
                dimension_[0], dimension_[1], dimension_[2], dimension_[3], dimension_[4], dimension_[5], dimension_[6], dimension_[7], dimension_[8], 
                order_, 
                derivative_[0], derivative_[1], derivative_[2], derivative_[3], derivative_[4], derivative_[5], derivative_[6], derivative_[7], derivative_[8], 
                x, y, z, s, p, r, a, q, u);
        }
        else
        {
            return (*bh_)(anchor[0], anchor[1], anchor[2], anchor[3], anchor[4], anchor[5], anchor[6], anchor[7], anchor[8]);
        }
    }
}
