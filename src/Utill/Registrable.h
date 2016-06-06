/*
 * Registrable.h
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */

#ifndef SRC_UTILL_REGISTRABLE_H_
#define SRC_UTILL_REGISTRABLE_H_

#include <functional>

#include "ofEvents.h"

struct do_register_trait {};
struct do_not_register_trait {};

class Registrable
{
public:

#ifdef TESTS
	typedef do_not_register_trait answer;
#else
	typedef do_register_trait answer;
#endif

	Registrable();
	virtual ~Registrable();

	void registerMe();
	void unregisterMe();

	template<class Event>
		static void notify(Event& event);
	template<class Event, typename Args>
		static void notify(Event& event, Args& args);
	template<class Event, typename Args>
		static void notify(Event& event, const Args& args);
private:
	virtual void registerMe(const do_register_trait&) = 0;
	virtual void unregisterMe(const do_register_trait&) = 0;

	template<class Event>
		static void notify(const do_register_trait&, Event& event);
	template<class Event, typename Args>
		static void notify(const do_register_trait&, Event& event, Args& args);
	template<class Event, typename Args>
		static void notify(const do_register_trait&, Event& event, const Args& args);

	void registerMe(const do_not_register_trait&);
	void unregisterMe(const do_not_register_trait&);

	template<class Event>
		static void notify(const do_not_register_trait&, Event& event);
	template<class Event, typename Args>
		static void notify(const do_not_register_trait&, Event& event, Args& args);
	template<class Event, typename Args>
		static void notify(const do_not_register_trait&, Event& event, const Args& args);
};

#include "Utill/Registrable.hpp"
#endif /* SRC_UTILL_REGISTRABLE_H_ */
