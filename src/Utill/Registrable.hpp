/*
 * Registrable.hpp
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */

#ifndef SRC_UTILL_REGISTRABLE_HPP_
#define SRC_UTILL_REGISTRABLE_HPP_


template<class Event, typename Args>
	void Registrable::notify(Event& event, Args& args)
{
	Registrable::notify(Registrable::answer(), event, args);
}

template<class Event, typename Args>
	void Registrable::notify(Event& event, const Args& args)
{
	Registrable::notify(Registrable::answer(), event, args);
}

template<class Event>
	void Registrable::notify(Event& event)
{
	Registrable::notify(Registrable::answer(), event);
}

template<class Event, typename Args>
	void Registrable::notify(const do_register_trait&, Event& event, Args& args)
{
	ofNotifyEvent(event, args);
}

template<class Event, typename Args>
	void Registrable::notify(const do_register_trait&, Event& event, const Args& args)
{
	ofNotifyEvent(event, args);
}

template<class Event>
	void Registrable::notify(const do_register_trait&, Event& event)
{
	ofNotifyEvent(event);
}

template<class Event, typename Args>
	void Registrable::notify(const do_not_register_trait&, Event& event, Args& args)
{
}

template<class Event, typename Args>
	void Registrable::notify(const do_not_register_trait&, Event& event, const Args& args)
{
}

template<class Event>
	void Registrable::notify(const do_not_register_trait&, Event& event)
{
}

#endif /* SRC_UTILL_REGISTRABLE_HPP_ */
