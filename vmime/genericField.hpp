//
// VMime library (http://www.vmime.org)
// Copyright (C) 2002-2005 Vincent Richard <vincent@vincent-richard.net>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#ifndef VMIME_GENERICFIELD_HPP_INCLUDED
#define VMIME_GENERICFIELD_HPP_INCLUDED


#include "vmime/headerField.hpp"
#include "vmime/headerFieldFactory.hpp"

#include "vmime/typeAdapter.hpp"


namespace vmime
{


/** Generic implementation for headerField.
  */

template <class VALUE_TYPE>
class genericField : virtual public headerField
{
	friend class vmime::creator;  // create ref

protected:

	genericField() : m_value(vmime::create <VALUE_TYPE>()) { }


	const ref <const component> getValueImp() const
	{
		return (m_value);
	}

	ref <component> getValueImp()
	{
		return (m_value);
	}

public:

	genericField <VALUE_TYPE>& operator=(const genericField <VALUE_TYPE>& other)
	{
		copyFrom(other);
		return (*this);
	}

	template <class TYPE>
	void setValue(const TYPE& value)
	{
		*m_value = value;
	}

	VALUE_TYPE& getValue()
	{
		return *m_value;
	}

	const VALUE_TYPE& getValue() const
	{
		return *m_value;
	}

	void setValue(const component& value)
	{
		const VALUE_TYPE& v = dynamic_cast <const VALUE_TYPE&>(value);
		*m_value = v;
	}

private:

	ref <VALUE_TYPE> m_value;
};


/** Generic implementation for headerField with a value of type 'string'.
  */

template <>
class genericField <string> : public genericField <typeAdapter <string> >
{
};


} // vmime


#endif // VMIME_GENERICFIELD_HPP_INCLUDED
