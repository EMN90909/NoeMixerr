// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019-2019 Johannes Lorenz <j.git$$$lorenz-ho.me, $$$=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MODEL_VISITOR_H
#define NoeMixerr_MODEL_VISITOR_H

namespace noemixerr
{


class AutomatableModel;
class BoolModel;
class IntModel;
class FloatModel;
class ComboBoxModel;
class TempoSyncKnobModel;

class ModelVisitor
{
	template<class ParentType = AutomatableModel, class ModelType>
	void up(ModelType& m) { visit(static_cast<ParentType&>(m)); }
public:
	virtual void visit(AutomatableModel& ) {}
	virtual void visit(BoolModel& m);
	virtual void visit(IntModel& m);
	virtual void visit(FloatModel& m);
	virtual void visit(ComboBoxModel& m);
	virtual void visit(TempoSyncKnobModel& m);
	virtual ~ModelVisitor() = default;
};

class ConstModelVisitor
{
	template<class ParentType = AutomatableModel, class ModelType>
	void up(const ModelType& m) {
		visit(static_cast<const ParentType&>(m)); }
public:
	virtual void visit(const AutomatableModel& ) {}
	virtual void visit(const BoolModel& m);
	virtual void visit(const IntModel& m);
	virtual void visit(const FloatModel& m);
	virtual void visit(const ComboBoxModel& m);
	virtual void visit(const TempoSyncKnobModel& m);
	virtual ~ConstModelVisitor() = default;
};


} // namespace noemixerr

#endif // NoeMixerr_MODEL_VISITOR_H
