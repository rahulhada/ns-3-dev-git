/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2015 University of Sussex
 * Copyright (c) 2015 Université Pierre et Marie Curie (UPMC)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author:  Matthieu Coudron <matthieu.coudron@lip6.fr>
 *
 */
#ifndef MPTCP_SCHEDULER_OWD_H
#define MPTCP_SCHEDULER_OWD_H


#include "ns3/mptcp-scheduler.h"
#include "ns3/object.h"
#include "ns3/ptr.h"
#include "ns3/mptcp-scheduler-round-robin.h"
#include "ns3/rtt-estimator.h"
#include "ns3/event-id.h"
#include <vector>
#include <list>

namespace ns3
{

class RttMeanDeviation;
class MpTcpSocketBase;
class MpTcpSubflow;


class ProbingRequest : public Object
{
public:
    ProbingRequest ();
    ~ProbingRequest ();
};

/**
 * This class contains characteristics of a pair of subflows
 * Estimations are always made from low to high id,
 * TODO copy latex code here
 */
class SubflowPair : public Object
{
  public:
    SubflowPair ();

//    RecordResult ();
    /**
     *
     * \param cookie Returned cookie to use
     *
     * \return True if it's ok to start
     */
    bool RecordStart (Ptr<MpTcpSubflow> sf, Time start,int *cookie);


    /**
     * Called upon reception of a DeltaOWD option answer
     * should be received on subflow which
     * \param sf To be able to rearm timer
     */
    void FinishRound (Ptr<MpTcpSubflow> sf, int cookie, uint64_t nanosec);

    EventId m_timer;
    // TODO utiliser un estimator qui
    RttMeanDeviation m_estimator; /* rename into DelayEstimator ? */
  protected:


    std::pair<Ptr<MpTcpSubflow>, Time> m_subflows[2];    /* */
    int m_index;    /**!< current index of m_subflows */

};

class MpTcpSchedulerOwd
//: public Object
: public MpTcpScheduler
{

public:
  static TypeId
  GetTypeId (void);

  MpTcpSchedulerOwd();
  virtual ~MpTcpSchedulerOwd ();


  void SetMeta(Ptr<MpTcpSocketBase> metaSock);

  /**
   * \brief This function is responsible for generating a list of packets to send
   *   and to specify on which subflow to send.
   *
   *   These *mappings* will be passed on to the meta socket that will send them without altering the
   *   mappings.
   *   It is of utmost importance to generate a perfect mapping !!! Any deviation
   *   from the foreseen mapping will trigger an error and crash the simulator
   *
   * \warn This function MUST NOT fiddle with metasockInternal
   * subflowId: pair(start,size)
   *
   * TODO should take into account backup priorities of subflows
  */
  virtual bool GenerateMapping(int& activeSubflowArrayId, SequenceNumber64& dsn, uint16_t& length);
  /**
  */
  // TODO
  // chooseSubflowForRetransmit

  /**
  Return Index of subflow to use
  */
  virtual Ptr<MpTcpSubflow> GetSubflowToUseForEmptyPacket ();


//  std::map<> ;
  std::list<EventId> m_timers;  /**< */
protected:
  uint8_t  m_lastUsedFlowId;        //!< keep track of last used subflow
  Ptr<MpTcpSocketBase> m_metaSock;  //!<
};


} // end of 'ns3'

#endif /* MPTCP_SCHEDULER_ROUND_ROBIN_H */