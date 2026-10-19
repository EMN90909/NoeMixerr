// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019-2019 Johannes Lorenz <j.git$$$lorenz-ho.me, $$$=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "ModelVisitor.h"

#include "AutomatableModel.h"
#include "ComboBoxModel.h"
#include "TempoSyncKnobModel.h"

namespace noemixerr
{


void ModelVisitor::visit(BoolModel &m) { up(m); }
void ModelVisitor::visit(IntModel &m) { up(m); }
void ModelVisitor::visit(FloatModel &m) { up(m); }
void ModelVisitor::visit(ComboBoxModel &m) { up<IntModel>(m); }
void ModelVisitor::visit(TempoSyncKnobModel &m) { up<FloatModel>(m); }

void ConstModelVisitor::visit(const BoolModel &m) { up(m); }
void ConstModelVisitor::visit(const IntModel &m) { up(m); }
void ConstModelVisitor::visit(const FloatModel &m) { up(m); }
void ConstModelVisitor::visit(const ComboBoxModel &m) { up<IntModel>(m); }
void ConstModelVisitor::visit(const TempoSyncKnobModel &m) { up<FloatModel>(m); }

} // namespace noemixerr