/*
 * Registrable.cc
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */

#include "Utill/Registrable.h"

Registrable::Registrable()
{
}

Registrable::~Registrable()
{
}

void Registrable::registerMe()
{
	registerMe(Registrable::answer());
}

void Registrable::unregisterMe()
{
	unregisterMe(Registrable::answer());
}

void Registrable::registerMe(const do_not_register_trait&)
{
}

void Registrable::unregisterMe(const do_not_register_trait&)
{
}

