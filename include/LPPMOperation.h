/* -------------------------------------------------------------------------------------
 * Copyright 2012 EPFL-I&C-LCA
 *
 * Designed and Developed by: Vincent Bindschaedler and Reza Shokri
 *
 * Authors: Reza Shokri, George Theodorakopoulos, Vincent Bindschaedler, George Danezis, 
 *          Jean-Pierre Hubaux, Jean-Yves Le Boudec
 * 
 * Contact: reza.shokri@epfl.ch
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this 
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 * 3. The name of the authors/developers may not be used to endorse or promote 
 *    products derived from this software without specific prior written permission.
 * 4. All advertising materials and/or any publications mentioning features or use of 
 *    this software must acknowledge it by citing the followings:
 *    [a] Location-Privacy Meter: A Tool to Quantify Location Privacy. 
 *        Available at http://lca.epfl.ch/projects/quantifyingprivacy/
 *    [b] Reza Shokri, George Theodorakopoulos, Jean-Yves Le Boudec, and Jean-Pierre 
 *        Hubaux. Quantifying Location Privacy. In IEEE Symposium on Security and 
 *        Privacy (S&P), Oakland, CA, USA, May 22-25, 2011.
 *    [c] Reza Shokri, George Theodorakopoulos, George Danezis, Jean-Pierre Hubaux, 
 *        and Jean-Yves Le Boudec. Quantifying Location Privacy: The Case of Sporadic
 *        Location Exposure. In The 11th Privacy Enhancing Technologies Symposium 
 *        (PETS), Waterloo, Canada, July 27-29, 2011.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * -------------------------------------------------------------------------------------
 */
#ifndef LPM_LPPMOPERATION_H
#define LPM_LPPMOPERATION_H

//!
//! \file
//!
#include <map>
using namespace std;
#include "FilterOperation.h"
#include <string>
using namespace std;

#include "Defs.h"
#include "Private.h"

namespace lpm { class Context; } 
namespace lpm { class Event; } 
namespace lpm { class ActualEvent; } 
namespace lpm { class ObservedEvent; } 
namespace lpm { class TraceSet; } 
namespace lpm { class ExposedEvent; } 

namespace lpm {


//! 
//! \brief Base class for all LPPM operations.
//! 
//! LPPM operations are filter operations which are able to distort events.
//!
class LPPMOperation : public FilterOperation 
{

  private:
    map<ull, ull> anonymization;

    void ComputeAnonymizationMap();


  public:
    LPPMOperation(string name);

    virtual ~LPPMOperation();

    virtual bool Filter(const Context* context, const Event* inEvent, Event** outEvent);

    //!   
    //! \brief Filters (i.e. distort) the input event 
    //!  
    //! \param[in] context 	Context*, the context.  
    //! \param[in] inEvent 	ActualEvent*, the event to filter.  
    //! \param[in] outEvent	ObservedEvent*, the filtered output event.  
    //!  
    //! \return true or false, depending on whether the call is successful  
    //!
    virtual bool Filter(const Context* context, const ActualEvent* inEvent, ObservedEvent** outEvent) = 0;

    double PDF(const Context* context, const Event* inEvent, const Event* outEvent) const;

    //! 
    //! \brief The probability density function (pdf) of the filter operation
    //!
    //! Computes and returns the probability that \a outEvent is the filtered output event conditional on the input event \a inEvent and the \a context.
    //!
    //! \param[in] context 	Context*, the context.
    //! \param[in] inEvent 	ActualEvent*, the event to filter.
    //! \param[in] outEvent	ObservedEvent*, the filtered output event.
    //!
    //! \return the value of the pdf as a double
    //!
    virtual double PDF(const Context* context, const ActualEvent* inEvent, const ObservedEvent* outEvent) const = 0;

    virtual string GetDetailString();


  protected:
    ull GetPseudonym(ull user) const;


  public:
    void GetAnonymizationMap(map<ull, ull>& map) const;

};

} // namespace lpm
#endif
