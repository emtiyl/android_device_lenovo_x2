/*
 * Copyright (C) 2013 Andreas Steffen
 * HSR Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#include "swid_tag_id.h"

typedef struct private_swid_tag_id_t private_swid_tag_id_t;

/**
 * Private data of a swid_tag_id_t object.
 *
 */
struct private_swid_tag_id_t {

	/**
	 * Public swid_tag_id_t interface.
	 */
	swid_tag_id_t public;

	/**
	 * Tag Creator
	 */
	chunk_t tag_creator;

	/**
	 * Unique Software ID
	 */
	chunk_t unique_sw_id;

	/**
	 * Optional Unique Sequence ID
	 */
	chunk_t unique_seq_id;

};

METHOD(swid_tag_id_t, get_tag_creator, chunk_t,
	private_swid_tag_id_t *this)
{
	return this->tag_creator;
}

METHOD(swid_tag_id_t, get_unique_sw_id, chunk_t,
	private_swid_tag_id_t *this, chunk_t *unique_seq_id)
{
	if (unique_seq_id)
	{
		*unique_seq_id = this->unique_seq_id;
	}
	return this->unique_sw_id;
}

METHOD(swid_tag_id_t, destroy, void,
	private_swid_tag_id_t *this)
{
	free(this->tag_creator.ptr);
	free(this->unique_sw_id.ptr);
	free(this->unique_seq_id.ptr);
	free(this);
}

/**
 * See header
 */
swid_tag_id_t *swid_tag_id_create(chunk_t tag_creator, chunk_t unique_sw_id,
								  chunk_t unique_seq_id)
{
	private_swid_tag_id_t *this;

	INIT(this,
		.public = {
			.get_tag_creator = _get_tag_creator,
			.get_unique_sw_id = _get_unique_sw_id,
			.destroy = _destroy,
		},
		.tag_creator = chunk_clone(tag_creator),
		.unique_sw_id = chunk_clone(unique_sw_id),
	);

	if (unique_seq_id.len > 0)
	{
		this->unique_seq_id = chunk_clone(unique_seq_id);
	}

	return &this->public;
}

