
/* related header files */
#include "ikfast_interface.h"
/* c system header files */

/* c++ standard library header files */

/* external project header files */

/* internal project header files */

#define APPROX_ITER 10 // Approximation iteration

namespace IKFAST_NAMESPACE
{

    bool IKFast_trans3D(const double trans[3], double solret[10][3])
    {
        IkReal eerot[9];
        IkReal eetrans[3];
        IkSolutionList<IkReal> solutions;
        std::vector<IkReal> vfree(GetNumFreeParameters());
        for (int i = 0; i < 3; ++i)
        {
            eetrans[i] = trans[i];
        }
        bool bSuccess = ComputeIk(eetrans, eerot, vfree.size() > 0 ? &vfree[0] : NULL, solutions);
        if (!bSuccess)
        {
            return -1;
        }
        else
        {
            std::vector<IkReal> solvalues(GetNumJoints());
            for (std::size_t i = 0; i < solutions.GetNumSolutions(); ++i)
            {
                const IkSolutionBase<IkReal> &sol = solutions.GetSolution(i);
                std::vector<IkReal> vsolfree(sol.GetFree().size());
                sol.GetSolution(&solvalues[0], vsolfree.size() > 0 ? &vsolfree[0] : NULL);
                for (std::size_t j = 0; j < solvalues.size(); ++j)
                    solret[i][j] = solvalues[j];
            }
            return 1;
        }
    }

    std::vector<std::vector<double>> IKFast_trans3D(const std::vector<double> trans, bool approx = false)
    {
        IkReal eerot[9];
        IkReal eetrans[3];
        IkReal eeorigin[3];
        IkReal eetmp[3];
        std::vector<std::vector<double>> solret;
        IkSolutionList<IkReal> solutions;
        std::vector<IkReal> vfree(GetNumFreeParameters());
        // Judge
        if ((!approx && trans.size() != 3) || (approx && trans.size() != 6))
        {
            throw std::invalid_argument("trans must be of size 3 (pos) when approx is False,\
                                         size 6 (pos, origin) when approx is True");
        }

        for (int i = 0; i < 3; ++i)
        {
            eetrans[i] = trans[i];
        }
        if (approx)
        {
            for (int i = 0; i < 3; ++i)
            {
                eeorigin[i] = trans[i + 3];
            }
        }
        bool bSuccess = ComputeIk(eetrans, eerot, vfree.size() > 0 ? &vfree[0] : NULL, solutions);
        if (!bSuccess)
        {
            // dichotomy
            if (approx)
            {
                for (int i = 0; i < APPROX_ITER; ++i)
                {
                    for (int j = 0; j < 3; ++j)
                    {
                        eetmp[j] = (eetrans[j] + eeorigin[j]) / 2;
                    }
                    bSuccess = ComputeIk(eetmp, eerot, vfree.size() > 0 ? &vfree[0] : NULL, solutions);
                    if (bSuccess)
                    {
                        for (int j = 0; j < 3; ++j)
                        {
                            eeorigin[j] = eetmp[j];
                        }
                    }
                    else
                    {
                        for (int j = 0; j < 3; ++j)
                        {
                            eetrans[j] = eetmp[j];
                        }
                    }
                }
                bSuccess = ComputeIk(eeorigin, eerot, vfree.size() > 0 ? &vfree[0] : NULL, solutions);
                if (!bSuccess) // dicotomy failed
                {
                    return solret;
                }
            }
            else
            {
                return solret;
            }
        }
        std::vector<IkReal> solvalues(GetNumJoints());
        for (std::size_t i = 0; i < solutions.GetNumSolutions(); ++i)
        {
            const IkSolutionBase<IkReal> &sol = solutions.GetSolution(i);
            std::vector<IkReal> vsolfree(sol.GetFree().size());
            sol.GetSolution(&solvalues[0], vsolfree.size() > 0 ? &vsolfree[0] : NULL);
            std::vector<double> solution;
            for (std::size_t j = 0; j < solvalues.size(); ++j)
                solution.emplace_back(solvalues[j]);
            solret.emplace_back(solution);
        }
        return solret;
    }

#ifdef USE_EIGEN
    std::vector<Eigen::Vector3d> IKFast_trans3D(const Eigen::Vector3d trans)
    {
        IkReal eerot[9];
        IkReal eetrans[3];
        IkSolutionList<IkReal> solutions;
        std::vector<IkReal> vfree(GetNumFreeParameters());
        std::vector<Eigen::Vector3d> solret;
        Eigen::Vector3d soltmp;
        for (int i = 0; i < 3; ++i)
        {
            eetrans[i] = trans[i];
        }
        bool bSuccess = ComputeIk(eetrans, eerot, vfree.size() > 0 ? &vfree[0] : NULL, solutions);
        if (bSuccess)
        {
            std::vector<IkReal> solvalues(GetNumJoints());
            for (std::size_t i = 0; i < solutions.GetNumSolutions(); ++i)
            {
                const IkSolutionBase<IkReal> &sol = solutions.GetSolution(i);
                std::vector<IkReal> vsolfree(sol.GetFree().size());
                sol.GetSolution(&solvalues[0], vsolfree.size() > 0 ? &vsolfree[0] : NULL);
                for (std::size_t j = 0; j < solvalues.size(); ++j)
                    soltmp[j] = solvalues[j];
                solret.emplace_back(soltmp);
            }
        }
        return solret;
    }
#endif

} // namespace IKFAST_NAMESPACE