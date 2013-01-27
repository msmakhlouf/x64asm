#include "src/instruction.h"

using namespace std;

namespace {

vector<const char*> att_ {{
	// Internal mnemonics
	"<label definition>"
	// Auto-generated mnemonics
	#include "src/opcode.att"
}};	

} // namespace

namespace x64asm {

OpSet Instruction::explicit_must_read_set() const {
	auto ret = OpSet::empty();
	for ( size_t i = 0, ie = arity(); i < ie; ++i ) {
		const auto o = get_operand(i);
		if ( const auto m = dynamic_cast<const M*>(o) )
			ret += *m;
		else if ( properties(i).contains(Property::MUST_READ) )
			o->insert_in(ret, false);
	}

	return ret;
}

OpSet Instruction::explicit_maybe_read_set() const {
	auto ret = OpSet::empty();
	for ( size_t i = 0, ie = arity(); i < ie; ++i ) {
		const auto o = get_operand(i);
		if ( const auto m = dynamic_cast<const M*>(o) )
			ret += *m;
		else if ( properties(i).contains(Property::MAYBE_READ) )
			o->insert_in(ret, false);
	}

	return ret;
}

OpSet Instruction::explicit_must_write_set() const {
	auto ret = OpSet::empty();
	for ( size_t i = 0, ie = arity(); i < ie; ++i ) {
		const auto o = get_operand(i);
		const auto p = properties(i);
		if ( p.contains(Property::MUST_WRITE_ZX) )
			o->insert_in(ret, true);
		else if ( p.contains(Property::MUST_WRITE) )
			o->insert_in(ret, false);
	}

	return ret;
}

OpSet Instruction::explicit_maybe_write_set() const {
	auto ret = OpSet::empty();
	for ( size_t i = 0, ie = arity(); i < ie; ++i ) {
		const auto o = get_operand(i);
		const auto p = properties(i);
		if ( p.contains(Property::MAYBE_WRITE_ZX) )
			o->insert_in(ret, true);
		else if ( p.contains(Property::MAYBE_WRITE) )
			o->insert_in(ret, false);
	}

	return ret;
}

OpSet Instruction::explicit_must_undef_set() const {
	auto ret = OpSet::empty();
	for ( size_t i = 0, ie = arity(); i < ie; ++i ) 
		if ( properties(i).contains(Property::MUST_UNDEF) )
			get_operand(i)->insert_in(ret, false);

	return ret;
}

OpSet Instruction::explicit_maybe_undef_set() const {
	auto ret = OpSet::empty();
	for ( size_t i = 0, ie = arity(); i < ie; ++i ) 
		if ( properties(i).contains(Property::MAYBE_UNDEF) )
			get_operand(i)->insert_in(ret, false);

	return ret;
}

bool Instruction::check() const {
	for ( size_t i = 0, ie = arity(); i < ie; ++i ) {
		const auto o = get_operand(i);
		if ( type(i) != o->type() || !o->check() )
			return false;
	}
	return true;
}

void Instruction::write_att(ostream& os) const {
	assert(get_opcode() < att_.size());
	os << att_[get_opcode()] << " ";

	if ( arity() > 0 )
		for ( size_t i = arity()-1; i >= 0; ++i ) {
			get_operand(i)->write_att(os);
			if ( i != 0 )
				os << ", ";
		}
}

void Instruction::write_intel(ostream& os) const {
}

vector<size_t> Instruction::arity_ {
	// Internal mnemonics
	0
	// Auto-generated mnemonics
	#include "src/arity.table"
};

vector<vector<Properties>> Instruction::properties_ {
	// Internal mnemonics
	{}
	// Auto-generated mnemonics
	#include "src/properties.table"
};

vector<vector<OpType>> Instruction::type_ {
	// Internal mnemonics
	{}
	// Auto-generated mnemonics
	#include "src/type.table"
};

vector<bool> Instruction::is_return_ {
	// Internal mnemonics
	false
	// Auto-generated mnemonics
	#include "src/return.table"
};

vector<bool> Instruction::is_nop_ {
	// Internal mnemonics
	false
	// Auto-generated mnemonics
	#include "src/nop.table"
};

vector<bool> Instruction::is_jump_ {
	// Internal mnemonics
	false
	// Auto-generated mnemonics
	#include "src/jump.table"
};

vector<bool> Instruction::is_cond_jump_ {
	// Internal mnemonics
	false
	// Auto-generated mnemonics
	#include "src/cond_jump.table"
};

vector<bool> Instruction::is_uncond_jump_ {
	// Internal mnemonics
	false
	// Auto-generated mnemonics
	#include "src/uncond_jump.table"
};

vector<OpSet> Instruction::implicit_must_read_set_ {
	// Internal mnemonics
	OpSet::empty()
	// Auto-generated mnemonics
	#include "src/must_read.table"
};

vector<OpSet> Instruction::implicit_maybe_read_set_ {
	// Internal mnemonics
	OpSet::empty()
	// Auto-generated mnemonics
	#include "src/maybe_read.table"
};

vector<OpSet> Instruction::implicit_must_write_set_ {
	// Internal mnemonics
	OpSet::empty()
	// Auto-generated mnemonics
	#include "src/must_write.table"
};

vector<OpSet> Instruction::implicit_maybe_write_set_ {
	// Internal mnemonics
	OpSet::empty()
	// Auto-generated mnemonics
	#include "src/maybe_write.table"
};

vector<OpSet> Instruction::implicit_must_undef_set_ {
	// Internal mnemonics
	OpSet::empty()
	// Auto-generated mnemonics
	#include "src/must_undef.table"
};

vector<OpSet> Instruction::implicit_maybe_undef_set_ {
	// Internal mnemonics
	OpSet::empty()
	// Auto-generated mnemonics
	#include "src/maybe_undef.table"
};

} // namespace x64asm
