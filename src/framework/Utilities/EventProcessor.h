/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __EVENTPROCESSOR_H
#define __EVENTPROCESSOR_H

#include "Platform/Define.h"

#include <map>
class EventProcessor;

class BasicEvent
{
	friend class EventProcessor;

	enum class AbortState : uint8
	{	
	STATE_RUNNING,
	STATE_ABORT_SCHEDULED,
	STATE_ABORTED
	};

	// Note. All times are in milliseconds here.


	public:
		BasicEvent()
			: m_abortState(AbortState::STATE_RUNNING), m_addTime(0), m_execTime(0) { }

        virtual ~BasicEvent()                               // override destructor to perform some actions on event removal
        { };

        // this method executes when the event is triggered
        // return false if event does not want to be deleted
        // e_time is execution time, p_time is update interval
        virtual bool Execute(uint64 /*e_time*/, uint32 /*p_time*/) { return true; }

        virtual bool IsDeletable() const { return true; }   // this event can be safely deleted

        virtual void Abort(uint64 /*e_time*/) {}            // this method executes when the event is aborted

        bool to_Abort;                                      // set by externals when the event is aborted, aborted events don't execute
        // and get Abort call when deleted

        // these can be used for time offset control

		// Aborts the event at the next update tick
		void ScheduleAbort();

	private:
		void SetAborted();
		bool IsRunning() const { return (m_abortState == AbortState::STATE_RUNNING); }
		bool IsAbortScheduled() const { return (m_abortState == AbortState::STATE_ABORT_SCHEDULED); }
		bool IsAborted() const { return (m_abortState == AbortState::STATE_ABORTED); }

		AbortState m_abortState;                            // set by externals when the event is aborted, aborted events don't execute


        uint64 m_addTime;                                   // time when the event was added to queue, filled by event handler
        uint64 m_execTime;                                  // planned time of next execution, filled by event handler
};

typedef std::multimap<uint64, BasicEvent*> EventList;

class EventProcessor
{
    public:

        EventProcessor() : m_time(0) { }
        ~EventProcessor();

        void Update(uint32 p_time);
        void KillAllEvents(bool force);
        void KillEvent(BasicEvent* Event);
        void AddEvent(BasicEvent* Event, uint64 e_time, bool set_addtime = true);
        uint64 CalculateTime(uint64 t_offset) const;
        EventList& GetEvents() { return m_events; }

    protected:

        uint64 m_time;
        EventList m_events;
        bool m_aborting;
};

#endif
