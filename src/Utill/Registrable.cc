/*
 * Registrable.cc
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */

#include "Utill/Registrable.h"

Registrable::Registrable() :
	registered_(false)
{
}

Registrable::~Registrable()
{
}

void Registrable::registerMe()
{
	if(!registered_)
	{
		registered_ = true;
		registerMe(Registrable::answer());
	}
}

void Registrable::unregisterMe()
{
	registered_ = false;
	unregisterMe(Registrable::answer());
}

void Registrable::registerMe(const do_not_register_trait&)
{
}

void Registrable::unregisterMe(const do_not_register_trait&)
{
}

