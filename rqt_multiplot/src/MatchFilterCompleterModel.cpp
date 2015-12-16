/******************************************************************************
 * Copyright (C) 2015 by Ralf Kaestner                                        *
 * ralf.kaestner@gmail.com                                                    *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include <iostream>

#include "rqt_multiplot/MatchFilterCompleterModel.h"

namespace rqt_multiplot {

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

MatchFilterCompleterModel::MatchFilterCompleterModel(QObject* parent,
    Qt::MatchFlags matchFlags, const QString& filterKey) :
  QSortFilterProxyModel(parent),
  matchFlags_(matchFlags),
  filterKey_(filterKey) {
}

MatchFilterCompleterModel::~MatchFilterCompleterModel() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

void MatchFilterCompleterModel::setMatchFlags(Qt::MatchFlags flags) {
  if (flags != matchFlags_) {
    matchFlags_ = flags;
    
    filterChanged();
  }
}

Qt::MatchFlags MatchFilterCompleterModel::getMatchFlags() const {
  return matchFlags_;
}

void MatchFilterCompleterModel::setFilterKey(const QString& key) {
  if (key != filterKey_) {
    filterKey_ = key;
    
    filterChanged();
  }
}

const QString& MatchFilterCompleterModel::getFilterKey() const {
  return filterKey_;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

bool MatchFilterCompleterModel::filterAcceptsRow(int sourceRow, const
    QModelIndex& sourceParent) const {
  if (matchFlags_ & Qt::MatchRegExp)
    return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
      
  if (filterKeyColumn() == -1)
    return true;
  
  QModelIndex sourceIndex = sourceModel()->index(sourceRow, filterKeyColumn(),
    sourceParent);
  
  if (!sourceIndex.isValid())
    return true;
  
  QString key = sourceModel()->data(sourceIndex, filterRole()).toString();  
  
  if (matchFlags_ & Qt::MatchContains)
    return key.contains(filterKey_, filterCaseSensitivity());
  else if (matchFlags_ & Qt::MatchStartsWith)
    return key.startsWith(filterKey_, filterCaseSensitivity());
  else if (matchFlags_ & Qt::MatchEndsWith)
    return key.endsWith(filterKey_, filterCaseSensitivity());
}

}
