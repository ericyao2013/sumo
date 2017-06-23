/****************************************************************************/
/// @file    GNEShapeh
/// @author  Pablo Alvarez Lopez
/// @date    Jun 2017
/// @version $Id: GNEPOI.cpp 23529 2017-03-18 10:22:36Z behrisch $
///
// Abstract class for Shapes uses in netedit
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright (C) 2001-2017 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This file is part of SUMO.
//   SUMO is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef GNEShape_h
#define GNEShape_h


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <string>
#include <utility>
#include <vector>
#include <netbuild/NBConnection.h>
#include <netbuild/NBEdge.h>
#include <netbuild/NBNode.h>
#include <utils/geom/Boundary.h>
#include <utils/geom/Position.h>
#include <utils/gui/globjects/GLIncludes.h>
#include <utils/gui/globjects/GUIGlObject.h>
#include <utils/gui/globjects/GUIGlObjectStorage.h>
#include <utils/gui/globjects/GUIPointOfInterest.h>
#include <utils/gui/globjects/GUIPolygon.h>
#include <utils/gui/settings/GUIPropertySchemeStorage.h>
#include <utils/xml/SUMOSAXHandler.h>
#include <utils/xml/SUMOXMLDefinitions.h>

#include "GNEAttributeCarrier.h"

// ===========================================================================
// class definitions
// ===========================================================================

class GNEShape : public GNEAttributeCarrier {
public:
    /**@brief Constructor.
     * @param[in] net The net to inform about gui updates
     * @param[in] tag sumo xml tag of the element
     * @param[in] icon GUIIcon associated to the additional
     */
    GNEShape(GNENet* net, SumoXMLTag tag, GUIIcon icon);

    /// @brief Destructor
    ~GNEShape();

    /// @brief get Net in which this element is placed
    GNENet* getNet() const;

    /// @name inherited from GUIPolygon/GUIPointOfInterest
    /// @{
    /**@brief Returns the name of the parent object
     * @return This object's parent id
     */
    virtual const std::string& getParentName() = 0;

    /**@brief Returns an own popup-menu
     *
     * @param[in] app The application needed to build the popup-menu
     * @param[in] parent The parent window needed to build the popup-menu
     * @return The built popup-menu
     * @see GUIGlObject::getPopUpMenu
     */
    virtual GUIGLObjectPopupMenu* getPopUpMenu(GUIMainWindow& app, GUISUMOAbstractView& parent) = 0;

    /**@brief Returns an own parameter window
     *
     * @param[in] app The application needed to build the parameter window
     * @param[in] parent The parent window needed to build the parameter window
     * @return The built parameter window
     * @see GUIGlObject::getParameterWindow
     */
    virtual GUIParameterTableWindow* getParameterWindow(GUIMainWindow& app, GUISUMOAbstractView& parent) = 0;

    /// @brief Returns the boundary to which the view shall be centered in order to show the object
    virtual Boundary getCenteringBoundary() const = 0;

    /**@brief Draws the object
     * @param[in] s The settings for the current view (may influence drawing)
     * @see GUIGlObject::drawGL
     */
    virtual void drawGL(const GUIVisualizationSettings& s) const = 0;
    /// @}

    /// @name inherited from GNEAttributeCarrier
    /// @{
    /* @brief method for getting the Attribute of an XML key
     * @param[in] key The attribute key
     * @return string with the value associated to key
     */
    virtual std::string getAttribute(SumoXMLAttr key) const = 0;

    /* @brief method for setting the attribute and letting the object perform additional changes
     * @param[in] key The attribute key
     * @param[in] value The new value
     * @param[in] undoList The undoList on which to register changes
     */
    virtual void setAttribute(SumoXMLAttr key, const std::string& value, GNEUndoList* undoList) = 0;

    /* @brief method for checking if the key and their conrrespond attribute are valids
     * @param[in] key The attribute key
     * @param[in] value The value asociated to key key
     * @return true if the value is valid, false in other case
     */
    virtual bool isValid(SumoXMLAttr key, const std::string& value) = 0;
    /// @}

protected:
    /// @brief the net to inform about updates
    GNENet* myNet;

private:
    /// @brief set attribute after validation
    virtual void setAttribute(SumoXMLAttr key, const std::string& value) = 0;

    /// @brief Invalidated copy constructor.
    GNEShape(const GNEShape&);

    /// @brief Invalidated assignment operator.
    GNEShape& operator=(const GNEShape&);
};


#endif

/****************************************************************************/
