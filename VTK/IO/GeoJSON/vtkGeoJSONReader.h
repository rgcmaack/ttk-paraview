/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkGeoJSONReader.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkGeoJSONReader
 * @brief   Convert Geo JSON format to vtkPolyData
 *
 * Outputs a vtkPolyData from the input
 * Geo JSON Data (http://www.geojson.org)
 */

#ifndef vtkGeoJSONReader_h
#define vtkGeoJSONReader_h

// VTK Includes
#include "vtkIOGeoJSONModule.h" // For export macro
#include "vtkPolyDataAlgorithm.h"

class vtkPolyData;

class VTKIOGEOJSON_EXPORT vtkGeoJSONReader : public vtkPolyDataAlgorithm
{
public:
  static vtkGeoJSONReader* New();
  vtkTypeMacro(vtkGeoJSONReader, vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  ///@{
  /**
   * Accessor for name of the file that will be opened on WriteData
   */
  vtkSetFilePathMacro(FileName);
  vtkGetFilePathMacro(FileName);
  ///@}

  ///@{
  /**
   * String used as data input (instead of file) when StringInputMode is enabled
   */
  vtkSetStringMacro(StringInput);
  vtkGetStringMacro(StringInput);
  ///@}

  ///@{
  /**
   * Set/get whether to use StringInput instead of reading input from file
   * The default is off
   */
  vtkSetMacro(StringInputMode, bool);
  vtkGetMacro(StringInputMode, bool);
  vtkBooleanMacro(StringInputMode, bool);
  ///@}

  ///@{
  /**
   * Set/get whether to convert all output polygons to triangles.
   * Note that if OutinePolygons mode is on, then no output polygons
   * are generated, and in that case, this option is not relevant.
   * The default is off.
   */
  vtkSetMacro(TriangulatePolygons, bool);
  vtkGetMacro(TriangulatePolygons, bool);
  vtkBooleanMacro(TriangulatePolygons, bool);
  ///@}

  ///@{
  /**
   * Set/get option to generate the border outlining each polygon,
   * so that the output cells for polygons are vtkPolyLine instances.
   * The default is off.
   */
  vtkSetMacro(OutlinePolygons, bool);
  vtkGetMacro(OutlinePolygons, bool);
  vtkBooleanMacro(OutlinePolygons, bool);
  ///@}

  ///@{
  /**
   * Set/get if data array for serialized GeoJSON "properties" should be created.
   */
  vtkSetMacro(SerializedPropertiesArray, bool);
  vtkGetMacro(SerializedPropertiesArray, bool);
  vtkBooleanMacro(SerializedPropertiesArray, bool);
  ///@}

  ///@{
  /**
   * Set/get name of data array for serialized GeoJSON "properties" node.
   * If specified, data will be stored as vtkCellData/vtkStringArray.
   */
  vtkSetStringMacro(SerializedPropertiesArrayName);
  vtkGetStringMacro(SerializedPropertiesArrayName);
  ///@}

  ///@{
  /**
   * Set/get feature names of data array for serialized GeoJSON "properties" node.
   * If specified, data will be stored as multiple arrays depending on the type.
   * Specify like name:defaultValue, name2:defaultValue
   * E.g. feature1:1,feature2:"House",feature3:0.0
   */
  vtkSetStringMacro(FeatureNamesInput);
  vtkGetStringMacro(FeatureNamesInput);
  ///@}

  /**
   * Specify feature property to read in with geometry objects
   * Note that defaultValue specifies both type & value
   */
  void AddFeatureProperty(const char* name, vtkVariant& typeAndDefaultValue);

  void AddFeatureProperties(const char* input);

protected:
  vtkGeoJSONReader();
  ~vtkGeoJSONReader() override;

  ///@{
  /**
   * Core implementation of the
   */
  int RequestData(vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) override;
  char* FileName;
  char* StringInput;
  char* FeatureNamesInput;
  bool StringInputMode;
  bool TriangulatePolygons;
  bool OutlinePolygons;
  bool SerializedPropertiesArray;
  char* SerializedPropertiesArrayName;
  ///@}

private:
  class GeoJSONReaderInternal;
  GeoJSONReaderInternal* Internal;

  vtkGeoJSONReader(const vtkGeoJSONReader&) = delete;
  void operator=(const vtkGeoJSONReader&) = delete;
};

#endif // vtkGeoJSONReader_h
