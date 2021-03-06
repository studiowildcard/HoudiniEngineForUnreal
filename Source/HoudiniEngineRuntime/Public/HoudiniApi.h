/*
 * Copyright (c) <2017> Side Effects Software Inc. *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 * COMMENTS:
 *      This file is generated. Do not modify directly.
 */

#pragma once
#include "HAPI.h"
#include "HAL/PlatformProcess.h"

#include "Core.h"
#include "CoreUObject.h"
#include "UObject/Class.h"
#include "UObject/CoreObject.h"
#include "UObject/CoreNet.h"
#include "Object.h"
#include "Math/NumericLimits.h"

#include "PhysicsEngine/BodyInstance.h"
#include "Engine.h"
#include "SlateCore.h"
#include "Slate.h"
#include "SlateApplication.h"

//JC: Stupid windows api issue
#ifdef GetGeoInfo
	#undef GetGeoInfo
#endif


struct HOUDINIENGINERUNTIME_API FHoudiniApi
{
public:

	static void InitializeHAPI(void* LibraryHandle);
	static void FinalizeHAPI();
	static bool IsHAPIInitialized();

public:

	typedef HAPI_Result (*AddAttributeFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, const HAPI_AttributeInfo * attr_info);
	typedef HAPI_Result (*AddGroupFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_GroupType group_type, const char * group_name);
	typedef HAPI_Result (*BindCustomImplementationFuncPtr)(HAPI_SessionType session_type, const char * dll_path);
	typedef HAPI_Result (*CheckForSpecificErrorsFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ErrorCodeBits errors_to_look_for, HAPI_ErrorCodeBits * errors_found);
	typedef HAPI_Result (*CleanupFuncPtr)(const HAPI_Session * session);
	typedef HAPI_Result (*CloseSessionFuncPtr)(const HAPI_Session * session);
	typedef HAPI_Result (*CommitGeoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id);
	typedef HAPI_Result (*ComposeChildNodeListFuncPtr)(const HAPI_Session * session, HAPI_NodeId parent_node_id, HAPI_NodeTypeBits node_type_filter, HAPI_NodeFlagsBits node_flags_filter, HAPI_Bool recursive, int * count);
	typedef HAPI_Result (*ComposeNodeCookResultFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_StatusVerbosity verbosity, int * buffer_length);
	typedef HAPI_Result (*ComposeObjectListFuncPtr)(const HAPI_Session * session, HAPI_NodeId parent_node_id, const char * categories, int * object_count);
	typedef HAPI_Result (*ConnectNodeInputFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, int input_index, HAPI_NodeId node_id_to_connect);
	typedef HAPI_Result (*ConvertMatrixToEulerFuncPtr)(const HAPI_Session * session, const float * matrix, HAPI_RSTOrder rst_order, HAPI_XYZOrder rot_order, HAPI_TransformEuler * transform_out);
	typedef HAPI_Result (*ConvertMatrixToQuatFuncPtr)(const HAPI_Session * session, const float * matrix, HAPI_RSTOrder rst_order, HAPI_Transform * transform_out);
	typedef HAPI_Result (*ConvertTransformFuncPtr)(const HAPI_Session * session, const HAPI_TransformEuler * transform_in, HAPI_RSTOrder rst_order, HAPI_XYZOrder rot_order, HAPI_TransformEuler * transform_out);
	typedef HAPI_Result (*ConvertTransformEulerToMatrixFuncPtr)(const HAPI_Session * session, const HAPI_TransformEuler * transform, float * matrix);
	typedef HAPI_Result (*ConvertTransformQuatToMatrixFuncPtr)(const HAPI_Session * session, const HAPI_Transform * transform, float * matrix);
	typedef HAPI_Result (*CookNodeFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const HAPI_CookOptions * cook_options);
	typedef HAPI_Result (*CreateCustomSessionFuncPtr)(HAPI_SessionType session_type, void * session_info, HAPI_Session * session);
	typedef HAPI_Result (*CreateInProcessSessionFuncPtr)(HAPI_Session * session);
	typedef HAPI_Result (*CreateInputNodeFuncPtr)(const HAPI_Session * session, HAPI_NodeId * node_id, const char * name);
	typedef HAPI_Result (*CreateNodeFuncPtr)(const HAPI_Session * session, HAPI_NodeId parent_node_id, const char * operator_name, const char * node_label, HAPI_Bool cook_on_creation, HAPI_NodeId * new_node_id);
	typedef HAPI_Result (*CreateThriftNamedPipeSessionFuncPtr)(HAPI_Session * session, const char * pipe_name);
	typedef HAPI_Result (*CreateThriftSocketSessionFuncPtr)(HAPI_Session * session, const char * host_name, int port);
	typedef HAPI_Result (*DeleteNodeFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id);
	typedef HAPI_Result (*DisconnectNodeInputFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, int input_index);
	typedef HAPI_Result (*ExtractImageToFileFuncPtr)(const HAPI_Session * session, HAPI_NodeId material_node_id, const char * image_file_format_name, const char * image_planes, const char * destination_folder_path, const char * destination_file_name, int * destination_file_path);
	typedef HAPI_Result (*ExtractImageToMemoryFuncPtr)(const HAPI_Session * session, HAPI_NodeId material_node_id, const char * image_file_format_name, const char * image_planes, int * buffer_size);
	typedef HAPI_Result (*GetActiveCacheCountFuncPtr)(const HAPI_Session * session, int * active_cache_count);
	typedef HAPI_Result (*GetActiveCacheNamesFuncPtr)(const HAPI_Session * session, HAPI_StringHandle * cache_names_array, int active_cache_count);
	typedef HAPI_Result (*GetAssetInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_AssetInfo * asset_info);
	typedef HAPI_Result (*GetAttributeFloat64DataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, HAPI_AttributeInfo * attr_info, int stride, double * data_array, int start, int length);
	typedef HAPI_Result (*GetAttributeFloatDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, HAPI_AttributeInfo * attr_info, int stride, float * data_array, int start, int length);
	typedef HAPI_Result (*GetAttributeInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, HAPI_AttributeOwner owner, HAPI_AttributeInfo * attr_info);
	typedef HAPI_Result (*GetAttributeInt64DataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, HAPI_AttributeInfo * attr_info, int stride, HAPI_Int64 * data_array, int start, int length);
	typedef HAPI_Result (*GetAttributeIntDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, HAPI_AttributeInfo * attr_info, int stride, int * data_array, int start, int length);
	typedef HAPI_Result (*GetAttributeNamesFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_AttributeOwner owner, HAPI_StringHandle * attribute_names_array, int count);
	typedef HAPI_Result (*GetAttributeStringDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, HAPI_AttributeInfo * attr_info, HAPI_StringHandle * data_array, int start, int length);
	typedef HAPI_Result (*GetAvailableAssetCountFuncPtr)(const HAPI_Session * session, HAPI_AssetLibraryId library_id, int * asset_count);
	typedef HAPI_Result (*GetAvailableAssetsFuncPtr)(const HAPI_Session * session, HAPI_AssetLibraryId library_id, HAPI_StringHandle * asset_names_array, int asset_count);
	typedef HAPI_Result (*GetBoxInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId geo_node_id, HAPI_PartId part_id, HAPI_BoxInfo * box_info);
	typedef HAPI_Result (*GetCachePropertyFuncPtr)(const HAPI_Session * session, const char * cache_name, HAPI_CacheProperty cache_property, int * property_value);
	typedef HAPI_Result (*GetComposedChildNodeListFuncPtr)(const HAPI_Session * session, HAPI_NodeId parent_node_id, HAPI_NodeId * child_node_ids_array, int count);
	typedef HAPI_Result (*GetComposedNodeCookResultFuncPtr)(const HAPI_Session * session, char * string_value, int length);
	typedef HAPI_Result (*GetComposedObjectListFuncPtr)(const HAPI_Session * session, HAPI_NodeId parent_node_id, HAPI_ObjectInfo * object_infos_array, int start, int length);
	typedef HAPI_Result (*GetComposedObjectTransformsFuncPtr)(const HAPI_Session * session, HAPI_NodeId parent_node_id, HAPI_RSTOrder rst_order, HAPI_Transform * transform_array, int start, int length);
	typedef HAPI_Result (*GetCookingCurrentCountFuncPtr)(const HAPI_Session * session, int * count);
	typedef HAPI_Result (*GetCookingTotalCountFuncPtr)(const HAPI_Session * session, int * count);
	typedef HAPI_Result (*GetCurveCountsFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int * counts_array, int start, int length);
	typedef HAPI_Result (*GetCurveInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_CurveInfo * info);
	typedef HAPI_Result (*GetCurveKnotsFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, float * knots_array, int start, int length);
	typedef HAPI_Result (*GetCurveOrdersFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int * orders_array, int start, int length);
	typedef HAPI_Result (*GetDisplayGeoInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId object_node_id, HAPI_GeoInfo * geo_info);
	typedef HAPI_Result (*GetEnvIntFuncPtr)(HAPI_EnvIntType int_type, int * value);
	typedef HAPI_Result (*GetFaceCountsFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int * face_counts_array, int start, int length);
	typedef HAPI_Result (*GetFirstVolumeTileFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_VolumeTileInfo * tile);
	typedef HAPI_Result (*GetGeoInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_GeoInfo * geo_info);
	typedef HAPI_Result (*GetGeoSizeFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * format, int * size);
	typedef HAPI_Result (*GetGroupCountOnPackedInstancePartFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int * pointGroupCount, int * primitiveGroupCount);
	typedef HAPI_Result (*GetGroupMembershipFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_GroupType group_type, const char * group_name, HAPI_Bool * membership_array_all_equal, int * membership_array, int start, int length);
	typedef HAPI_Result (*GetGroupMembershipOnPackedInstancePartFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_GroupType group_type, const char * group_name, HAPI_Bool * membership_array_all_equal, int * membership_array, int start, int length);
	typedef HAPI_Result (*GetGroupNamesFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_GroupType group_type, HAPI_StringHandle * group_names_array, int group_count);
	typedef HAPI_Result (*GetGroupNamesOnPackedInstancePartFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_GroupType group_type, HAPI_StringHandle * group_names_array, int group_count);
	typedef HAPI_Result (*GetHandleBindingInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, int handle_index, HAPI_HandleBindingInfo * handle_binding_infos_array, int start, int length);
	typedef HAPI_Result (*GetHandleInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_HandleInfo * handle_infos_array, int start, int length);
	typedef HAPI_Result (*GetHeightFieldDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, float * values_array, int start, int length);
	typedef HAPI_Result (*GetImageInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId material_node_id, HAPI_ImageInfo * image_info);
	typedef HAPI_Result (*GetImageMemoryBufferFuncPtr)(const HAPI_Session * session, HAPI_NodeId material_node_id, char * buffer, int length);
	typedef HAPI_Result (*GetImagePlaneCountFuncPtr)(const HAPI_Session * session, HAPI_NodeId material_node_id, int * image_plane_count);
	typedef HAPI_Result (*GetImagePlanesFuncPtr)(const HAPI_Session * session, HAPI_NodeId material_node_id, HAPI_StringHandle * image_planes_array, int image_plane_count);
	typedef HAPI_Result (*GetInstanceTransformsFuncPtr)(const HAPI_Session * session, HAPI_NodeId object_node_id, HAPI_RSTOrder rst_order, HAPI_Transform * transforms_array, int start, int length);
	typedef HAPI_Result (*GetInstancedObjectIdsFuncPtr)(const HAPI_Session * session, HAPI_NodeId object_node_id, HAPI_NodeId * instanced_node_id_array, int start, int length);
	typedef HAPI_Result (*GetInstancedPartIdsFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_PartId * instanced_parts_array, int start, int length);
	typedef HAPI_Result (*GetInstancerPartTransformsFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_RSTOrder rst_order, HAPI_Transform * transforms_array, int start, int length);
	typedef HAPI_Result (*GetManagerNodeIdFuncPtr)(const HAPI_Session * session, HAPI_NodeType node_type, HAPI_NodeId * node_id);
	typedef HAPI_Result (*GetMaterialInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId material_node_id, HAPI_MaterialInfo * material_info);
	typedef HAPI_Result (*GetMaterialNodeIdsOnFacesFuncPtr)(const HAPI_Session * session, HAPI_NodeId geometry_node_id, HAPI_PartId part_id, HAPI_Bool * are_all_the_same, HAPI_NodeId * material_ids_array, int start, int length);
	typedef HAPI_Result (*GetNextVolumeTileFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_VolumeTileInfo * tile);
	typedef HAPI_Result (*GetNodeInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_NodeInfo * node_info);
	typedef HAPI_Result (*GetNodeInputNameFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, int input_idx, HAPI_StringHandle * name);
	typedef HAPI_Result (*GetNodePathFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_NodeId relative_to_node_id, HAPI_StringHandle * path);
	typedef HAPI_Result (*GetObjectInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ObjectInfo * object_info);
	typedef HAPI_Result (*GetObjectTransformFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_NodeId relative_to_node_id, HAPI_RSTOrder rst_order, HAPI_Transform * transform);
	typedef HAPI_Result (*GetParametersFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmInfo * parm_infos_array, int start, int length);
	typedef HAPI_Result (*GetParmChoiceListsFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmChoiceInfo *parm_choices_array, int start, int length);
	typedef HAPI_Result (*GetParmFileFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, const char * destination_directory, const char * destination_file_name);
	typedef HAPI_Result (*GetParmFloatValueFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, int index, float * value);
	typedef HAPI_Result (*GetParmFloatValuesFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, float * values_array, int start, int length);
	typedef HAPI_Result (*GetParmIdFromNameFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, HAPI_ParmId * parm_id);
	typedef HAPI_Result (*GetParmInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmId parm_id, HAPI_ParmInfo * parm_info);
	typedef HAPI_Result (*GetParmInfoFromNameFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, HAPI_ParmInfo * parm_info);
	typedef HAPI_Result (*GetParmIntValueFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, int index, int * value);
	typedef HAPI_Result (*GetParmIntValuesFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, int * values_array, int start, int length);
	typedef HAPI_Result (*GetParmNodeValueFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, HAPI_NodeId * value);
	typedef HAPI_Result (*GetParmStringValueFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, int index, HAPI_Bool evaluate, HAPI_StringHandle * value);
	typedef HAPI_Result (*GetParmStringValuesFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_Bool evaluate, HAPI_StringHandle * values_array, int start, int length);
	typedef HAPI_Result (*GetParmTagNameFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmId parm_id, int tag_index, HAPI_StringHandle * tag_name);
	typedef HAPI_Result (*GetParmTagValueFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmId parm_id, const char * tag_name, HAPI_StringHandle * tag_value);
	typedef HAPI_Result (*GetParmWithTagFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * tag_name, HAPI_ParmId * parm_id);
	typedef HAPI_Result (*GetPartInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_PartInfo * part_info);
	typedef HAPI_Result (*GetPresetFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, char * buffer, int buffer_length);
	typedef HAPI_Result (*GetPresetBufLengthFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PresetType preset_type, const char * preset_name, int * buffer_length);
	typedef HAPI_Result (*GetServerEnvIntFuncPtr)(const HAPI_Session * session, const char * variable_name, int * value);
	typedef HAPI_Result (*GetServerEnvStringFuncPtr)(const HAPI_Session * session, const char * variable_name, HAPI_StringHandle * value);
	typedef HAPI_Result (*GetSessionEnvIntFuncPtr)(const HAPI_Session * session, HAPI_SessionEnvIntType int_type, int * value);
	typedef HAPI_Result (*GetSphereInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId geo_node_id, HAPI_PartId part_id, HAPI_SphereInfo * sphere_info);
	typedef HAPI_Result (*GetStatusFuncPtr)(const HAPI_Session * session, HAPI_StatusType status_type, int * status);
	typedef HAPI_Result (*GetStatusStringFuncPtr)(const HAPI_Session * session, HAPI_StatusType status_type, char * string_value, int length);
	typedef HAPI_Result (*GetStatusStringBufLengthFuncPtr)(const HAPI_Session * session, HAPI_StatusType status_type, HAPI_StatusVerbosity verbosity, int * buffer_length);
	typedef HAPI_Result (*GetStringFuncPtr)(const HAPI_Session * session, HAPI_StringHandle string_handle, char * string_value, int length);
	typedef HAPI_Result (*GetStringBufLengthFuncPtr)(const HAPI_Session * session, HAPI_StringHandle string_handle, int * buffer_length);
	typedef HAPI_Result (*GetSupportedImageFileFormatCountFuncPtr)(const HAPI_Session * session, int * file_format_count);
	typedef HAPI_Result (*GetSupportedImageFileFormatsFuncPtr)(const HAPI_Session * session, HAPI_ImageFileFormat * formats_array, int file_format_count);
	typedef HAPI_Result (*GetTimeFuncPtr)(const HAPI_Session * session, float * time);
	typedef HAPI_Result (*GetTimelineOptionsFuncPtr)(const HAPI_Session * session, HAPI_TimelineOptions * timeline_options);
	typedef HAPI_Result (*GetVertexListFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int * vertex_list_array, int start, int length);
	typedef HAPI_Result (*GetVolumeBoundsFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, float * x_min, float * y_min, float * z_min, float * x_max, float * y_max, float * z_max, float * x_center, float * y_center, float * z_center);
	typedef HAPI_Result (*GetVolumeInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_VolumeInfo * volume_info);
	typedef HAPI_Result (*GetVolumeTileFloatDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, float fill_value, const HAPI_VolumeTileInfo * tile, float * values_array, int length);
	typedef HAPI_Result (*GetVolumeTileIntDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int fill_value, const HAPI_VolumeTileInfo * tile, int * values_array, int length);
	typedef HAPI_Result (*GetVolumeVoxelFloatDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int x_index, int y_index, int z_index, float * values_array, int value_count);
	typedef HAPI_Result (*GetVolumeVoxelIntDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int x_index, int y_index, int z_index, int * values_array, int value_count);
	typedef HAPI_Result (*InitializeFuncPtr)(const HAPI_Session * session, const HAPI_CookOptions * cook_options, HAPI_Bool use_cooking_thread, int cooking_thread_stack_size, const char * houdini_environment_files, const char * otl_search_path, const char * dso_search_path, const char * image_dso_search_path, const char * audio_dso_search_path);
	typedef HAPI_Result (*InsertMultiparmInstanceFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmId parm_id, int instance_position);
	typedef HAPI_Result (*InterruptFuncPtr)(const HAPI_Session * session);
	typedef HAPI_Result (*IsInitializedFuncPtr)(const HAPI_Session * session);
	typedef HAPI_Result (*IsNodeValidFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, int unique_node_id, HAPI_Bool * answer);
	typedef HAPI_Result (*IsSessionValidFuncPtr)(const HAPI_Session * session);
	typedef HAPI_Result (*LoadAssetLibraryFromFileFuncPtr)(const HAPI_Session * session, const char * file_path, HAPI_Bool allow_overwrite, HAPI_AssetLibraryId* library_id);
	typedef HAPI_Result (*LoadAssetLibraryFromMemoryFuncPtr)(const HAPI_Session * session, const char * library_buffer, int library_buffer_length, HAPI_Bool allow_overwrite, HAPI_AssetLibraryId * library_id);
	typedef HAPI_Result (*LoadGeoFromFileFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * file_name);
	typedef HAPI_Result (*LoadGeoFromMemoryFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * format, const char * buffer, int length);
	typedef HAPI_Result (*LoadHIPFileFuncPtr)(const HAPI_Session * session, const char * file_name, HAPI_Bool cook_on_load);
	typedef HAPI_Result (*ParmHasTagFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmId parm_id, const char * tag_name, HAPI_Bool * has_tag);
	typedef HAPI_Result (*PythonThreadInterpreterLockFuncPtr)(const HAPI_Session * session, HAPI_Bool locked);
	typedef HAPI_Result (*QueryNodeInputFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_to_query, int input_index, HAPI_NodeId * connected_node_id);
	typedef HAPI_Result (*RemoveMultiparmInstanceFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmId parm_id, int instance_position);
	typedef HAPI_Result (*RenameNodeFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * new_name);
	typedef HAPI_Result (*RenderCOPToImageFuncPtr)(const HAPI_Session * session, HAPI_NodeId cop_node_id);
	typedef HAPI_Result (*RenderTextureToImageFuncPtr)(const HAPI_Session * session, HAPI_NodeId material_node_id, HAPI_ParmId parm_id);
	typedef HAPI_Result (*ResetSimulationFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id);
	typedef HAPI_Result (*RevertGeoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id);
	typedef HAPI_Result (*SaveGeoToFileFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * file_name);
	typedef HAPI_Result (*SaveGeoToMemoryFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, char * buffer, int length);
	typedef HAPI_Result (*SaveHIPFileFuncPtr)(const HAPI_Session * session, const char * file_path, HAPI_Bool lock_nodes);
	typedef HAPI_Result (*SetAnimCurveFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmId parm_id, int parm_index, const HAPI_Keyframe * curve_keyframes_array, int keyframe_count);
	typedef HAPI_Result (*SetAttributeFloat64DataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, const HAPI_AttributeInfo * attr_info, const double * data_array, int start, int length);
	typedef HAPI_Result (*SetAttributeFloatDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, const HAPI_AttributeInfo * attr_info, const float * data_array, int start, int length);
	typedef HAPI_Result (*SetAttributeInt64DataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, const HAPI_AttributeInfo * attr_info, const HAPI_Int64 * data_array, int start, int length);
	typedef HAPI_Result (*SetAttributeIntDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, const HAPI_AttributeInfo * attr_info, const int * data_array, int start, int length);
	typedef HAPI_Result (*SetAttributeStringDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, const HAPI_AttributeInfo *attr_info, const char ** data_array, int start, int length);
	typedef HAPI_Result (*SetCachePropertyFuncPtr)(const HAPI_Session * session, const char * cache_name, HAPI_CacheProperty cache_property, int property_value);
	typedef HAPI_Result (*SetCurveCountsFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const int * counts_array, int start, int length);
	typedef HAPI_Result (*SetCurveInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const HAPI_CurveInfo * info);
	typedef HAPI_Result (*SetCurveKnotsFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const float * knots_array, int start, int length);
	typedef HAPI_Result (*SetCurveOrdersFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const int * orders_array, int start, int length);
	typedef HAPI_Result (*SetFaceCountsFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const int * face_counts_array, int start, int length);
	typedef HAPI_Result (*SetGroupMembershipFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_GroupType group_type, const char * group_name, const int * membership_array, int start, int length);
	typedef HAPI_Result (*SetHeightFieldDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, const float * values_array, int start, int length);
	typedef HAPI_Result (*SetImageInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId material_node_id, const HAPI_ImageInfo * image_info);
	typedef HAPI_Result (*SetObjectTransformFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const HAPI_TransformEuler * trans);
	typedef HAPI_Result (*SetParmFloatValueFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, int index, float value);
	typedef HAPI_Result (*SetParmFloatValuesFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const float * values_array, int start, int length);
	typedef HAPI_Result (*SetParmIntValueFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, int index, int value);
	typedef HAPI_Result (*SetParmIntValuesFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const int * values_array, int start, int length);
	typedef HAPI_Result (*SetParmNodeValueFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, HAPI_NodeId value);
	typedef HAPI_Result (*SetParmStringValueFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, const char * value, HAPI_ParmId parm_id, int index);
	typedef HAPI_Result (*SetPartInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const HAPI_PartInfo * part_info);
	typedef HAPI_Result (*SetPresetFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PresetType preset_type, const char * preset_name, const char * buffer, int buffer_length);
	typedef HAPI_Result (*SetServerEnvIntFuncPtr)(const HAPI_Session * session, const char * variable_name, int value);
	typedef HAPI_Result (*SetServerEnvStringFuncPtr)(const HAPI_Session * session, const char * variable_name, const char * value);
	typedef HAPI_Result (*SetTimeFuncPtr)(const HAPI_Session * session, float time);
	typedef HAPI_Result (*SetTimelineOptionsFuncPtr)(const HAPI_Session * session, const HAPI_TimelineOptions * timeline_options);
	typedef HAPI_Result (*SetTransformAnimCurveFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_TransformComponent trans_comp, const HAPI_Keyframe * curve_keyframes_array, int keyframe_count);
	typedef HAPI_Result (*SetVertexListFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const int * vertex_list_array, int start, int length);
	typedef HAPI_Result (*SetVolumeInfoFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const HAPI_VolumeInfo * volume_info);
	typedef HAPI_Result (*SetVolumeTileFloatDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const HAPI_VolumeTileInfo * tile, const float * values_array, int length);
	typedef HAPI_Result (*SetVolumeTileIntDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const HAPI_VolumeTileInfo * tile, const int * values_array, int length);
	typedef HAPI_Result (*SetVolumeVoxelFloatDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int x_index, int y_index, int z_index, const float * values_array, int value_count);
	typedef HAPI_Result (*SetVolumeVoxelIntDataFuncPtr)(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int x_index, int y_index, int z_index, const int * values_array, int value_count);
	typedef HAPI_Result (*StartThriftNamedPipeServerFuncPtr)(const HAPI_ThriftServerOptions * options, const char * pipe_name, HAPI_ProcessId * process_id);
	typedef HAPI_Result (*StartThriftSocketServerFuncPtr)(const HAPI_ThriftServerOptions * options, int port, HAPI_ProcessId * process_id);

public:

	static AddAttributeFuncPtr AddAttribute;
	static AddGroupFuncPtr AddGroup;
	static BindCustomImplementationFuncPtr BindCustomImplementation;
	static CheckForSpecificErrorsFuncPtr CheckForSpecificErrors;
	static CleanupFuncPtr Cleanup;
	static CloseSessionFuncPtr CloseSession;
	static CommitGeoFuncPtr CommitGeo;
	static ComposeChildNodeListFuncPtr ComposeChildNodeList;
	static ComposeNodeCookResultFuncPtr ComposeNodeCookResult;
	static ComposeObjectListFuncPtr ComposeObjectList;
	static ConnectNodeInputFuncPtr ConnectNodeInput;
	static ConvertMatrixToEulerFuncPtr ConvertMatrixToEuler;
	static ConvertMatrixToQuatFuncPtr ConvertMatrixToQuat;
	static ConvertTransformFuncPtr ConvertTransform;
	static ConvertTransformEulerToMatrixFuncPtr ConvertTransformEulerToMatrix;
	static ConvertTransformQuatToMatrixFuncPtr ConvertTransformQuatToMatrix;
	static CookNodeFuncPtr CookNode;
	static CreateCustomSessionFuncPtr CreateCustomSession;
	static CreateInProcessSessionFuncPtr CreateInProcessSession;
	static CreateInputNodeFuncPtr CreateInputNode;
	static CreateNodeFuncPtr CreateNode;
	static CreateThriftNamedPipeSessionFuncPtr CreateThriftNamedPipeSession;
	static CreateThriftSocketSessionFuncPtr CreateThriftSocketSession;
	static DeleteNodeFuncPtr DeleteNode;
	static DisconnectNodeInputFuncPtr DisconnectNodeInput;
	static ExtractImageToFileFuncPtr ExtractImageToFile;
	static ExtractImageToMemoryFuncPtr ExtractImageToMemory;
	static GetActiveCacheCountFuncPtr GetActiveCacheCount;
	static GetActiveCacheNamesFuncPtr GetActiveCacheNames;
	static GetAssetInfoFuncPtr GetAssetInfo;
	static GetAttributeFloat64DataFuncPtr GetAttributeFloat64Data;
	static GetAttributeFloatDataFuncPtr GetAttributeFloatData;
	static GetAttributeInfoFuncPtr GetAttributeInfo;
	static GetAttributeInt64DataFuncPtr GetAttributeInt64Data;
	static GetAttributeIntDataFuncPtr GetAttributeIntData;
	static GetAttributeNamesFuncPtr GetAttributeNames;
	static GetAttributeStringDataFuncPtr GetAttributeStringData;
	static GetAvailableAssetCountFuncPtr GetAvailableAssetCount;
	static GetAvailableAssetsFuncPtr GetAvailableAssets;
	static GetBoxInfoFuncPtr GetBoxInfo;
	static GetCachePropertyFuncPtr GetCacheProperty;
	static GetComposedChildNodeListFuncPtr GetComposedChildNodeList;
	static GetComposedNodeCookResultFuncPtr GetComposedNodeCookResult;
	static GetComposedObjectListFuncPtr GetComposedObjectList;
	static GetComposedObjectTransformsFuncPtr GetComposedObjectTransforms;
	static GetCookingCurrentCountFuncPtr GetCookingCurrentCount;
	static GetCookingTotalCountFuncPtr GetCookingTotalCount;
	static GetCurveCountsFuncPtr GetCurveCounts;
	static GetCurveInfoFuncPtr GetCurveInfo;
	static GetCurveKnotsFuncPtr GetCurveKnots;
	static GetCurveOrdersFuncPtr GetCurveOrders;
	static GetDisplayGeoInfoFuncPtr GetDisplayGeoInfo;
	static GetEnvIntFuncPtr GetEnvInt;
	static GetFaceCountsFuncPtr GetFaceCounts;
	static GetFirstVolumeTileFuncPtr GetFirstVolumeTile;
	static GetGeoInfoFuncPtr GetGeoInfo;
	static GetGeoSizeFuncPtr GetGeoSize;
	static GetGroupCountOnPackedInstancePartFuncPtr GetGroupCountOnPackedInstancePart;
	static GetGroupMembershipFuncPtr GetGroupMembership;
	static GetGroupMembershipOnPackedInstancePartFuncPtr GetGroupMembershipOnPackedInstancePart;
	static GetGroupNamesFuncPtr GetGroupNames;
	static GetGroupNamesOnPackedInstancePartFuncPtr GetGroupNamesOnPackedInstancePart;
	static GetHandleBindingInfoFuncPtr GetHandleBindingInfo;
	static GetHandleInfoFuncPtr GetHandleInfo;
	static GetHeightFieldDataFuncPtr GetHeightFieldData;
	static GetImageInfoFuncPtr GetImageInfo;
	static GetImageMemoryBufferFuncPtr GetImageMemoryBuffer;
	static GetImagePlaneCountFuncPtr GetImagePlaneCount;
	static GetImagePlanesFuncPtr GetImagePlanes;
	static GetInstanceTransformsFuncPtr GetInstanceTransforms;
	static GetInstancedObjectIdsFuncPtr GetInstancedObjectIds;
	static GetInstancedPartIdsFuncPtr GetInstancedPartIds;
	static GetInstancerPartTransformsFuncPtr GetInstancerPartTransforms;
	static GetManagerNodeIdFuncPtr GetManagerNodeId;
	static GetMaterialInfoFuncPtr GetMaterialInfo;
	static GetMaterialNodeIdsOnFacesFuncPtr GetMaterialNodeIdsOnFaces;
	static GetNextVolumeTileFuncPtr GetNextVolumeTile;
	static GetNodeInfoFuncPtr GetNodeInfo;
	static GetNodeInputNameFuncPtr GetNodeInputName;
	static GetNodePathFuncPtr GetNodePath;
	static GetObjectInfoFuncPtr GetObjectInfo;
	static GetObjectTransformFuncPtr GetObjectTransform;
	static GetParametersFuncPtr GetParameters;
	static GetParmChoiceListsFuncPtr GetParmChoiceLists;
	static GetParmFileFuncPtr GetParmFile;
	static GetParmFloatValueFuncPtr GetParmFloatValue;
	static GetParmFloatValuesFuncPtr GetParmFloatValues;
	static GetParmIdFromNameFuncPtr GetParmIdFromName;
	static GetParmInfoFuncPtr GetParmInfo;
	static GetParmInfoFromNameFuncPtr GetParmInfoFromName;
	static GetParmIntValueFuncPtr GetParmIntValue;
	static GetParmIntValuesFuncPtr GetParmIntValues;
	static GetParmNodeValueFuncPtr GetParmNodeValue;
	static GetParmStringValueFuncPtr GetParmStringValue;
	static GetParmStringValuesFuncPtr GetParmStringValues;
	static GetParmTagNameFuncPtr GetParmTagName;
	static GetParmTagValueFuncPtr GetParmTagValue;
	static GetParmWithTagFuncPtr GetParmWithTag;
	static GetPartInfoFuncPtr GetPartInfo;
	static GetPresetFuncPtr GetPreset;
	static GetPresetBufLengthFuncPtr GetPresetBufLength;
	static GetServerEnvIntFuncPtr GetServerEnvInt;
	static GetServerEnvStringFuncPtr GetServerEnvString;
	static GetSessionEnvIntFuncPtr GetSessionEnvInt;
	static GetSphereInfoFuncPtr GetSphereInfo;
	static GetStatusFuncPtr GetStatus;
	static GetStatusStringFuncPtr GetStatusString;
	static GetStatusStringBufLengthFuncPtr GetStatusStringBufLength;
	static GetStringFuncPtr GetString;
	static GetStringBufLengthFuncPtr GetStringBufLength;
	static GetSupportedImageFileFormatCountFuncPtr GetSupportedImageFileFormatCount;
	static GetSupportedImageFileFormatsFuncPtr GetSupportedImageFileFormats;
	static GetTimeFuncPtr GetTime;
	static GetTimelineOptionsFuncPtr GetTimelineOptions;
	static GetVertexListFuncPtr GetVertexList;
	static GetVolumeBoundsFuncPtr GetVolumeBounds;
	static GetVolumeInfoFuncPtr GetVolumeInfo;
	static GetVolumeTileFloatDataFuncPtr GetVolumeTileFloatData;
	static GetVolumeTileIntDataFuncPtr GetVolumeTileIntData;
	static GetVolumeVoxelFloatDataFuncPtr GetVolumeVoxelFloatData;
	static GetVolumeVoxelIntDataFuncPtr GetVolumeVoxelIntData;
	static InitializeFuncPtr Initialize;
	static InsertMultiparmInstanceFuncPtr InsertMultiparmInstance;
	static InterruptFuncPtr Interrupt;
	static IsInitializedFuncPtr IsInitialized;
	static IsNodeValidFuncPtr IsNodeValid;
	static IsSessionValidFuncPtr IsSessionValid;
	static LoadAssetLibraryFromFileFuncPtr LoadAssetLibraryFromFile;
	static LoadAssetLibraryFromMemoryFuncPtr LoadAssetLibraryFromMemory;
	static LoadGeoFromFileFuncPtr LoadGeoFromFile;
	static LoadGeoFromMemoryFuncPtr LoadGeoFromMemory;
	static LoadHIPFileFuncPtr LoadHIPFile;
	static ParmHasTagFuncPtr ParmHasTag;
	static PythonThreadInterpreterLockFuncPtr PythonThreadInterpreterLock;
	static QueryNodeInputFuncPtr QueryNodeInput;
	static RemoveMultiparmInstanceFuncPtr RemoveMultiparmInstance;
	static RenameNodeFuncPtr RenameNode;
	static RenderCOPToImageFuncPtr RenderCOPToImage;
	static RenderTextureToImageFuncPtr RenderTextureToImage;
	static ResetSimulationFuncPtr ResetSimulation;
	static RevertGeoFuncPtr RevertGeo;
	static SaveGeoToFileFuncPtr SaveGeoToFile;
	static SaveGeoToMemoryFuncPtr SaveGeoToMemory;
	static SaveHIPFileFuncPtr SaveHIPFile;
	static SetAnimCurveFuncPtr SetAnimCurve;
	static SetAttributeFloat64DataFuncPtr SetAttributeFloat64Data;
	static SetAttributeFloatDataFuncPtr SetAttributeFloatData;
	static SetAttributeInt64DataFuncPtr SetAttributeInt64Data;
	static SetAttributeIntDataFuncPtr SetAttributeIntData;
	static SetAttributeStringDataFuncPtr SetAttributeStringData;
	static SetCachePropertyFuncPtr SetCacheProperty;
	static SetCurveCountsFuncPtr SetCurveCounts;
	static SetCurveInfoFuncPtr SetCurveInfo;
	static SetCurveKnotsFuncPtr SetCurveKnots;
	static SetCurveOrdersFuncPtr SetCurveOrders;
	static SetFaceCountsFuncPtr SetFaceCounts;
	static SetGroupMembershipFuncPtr SetGroupMembership;
	static SetHeightFieldDataFuncPtr SetHeightFieldData;
	static SetImageInfoFuncPtr SetImageInfo;
	static SetObjectTransformFuncPtr SetObjectTransform;
	static SetParmFloatValueFuncPtr SetParmFloatValue;
	static SetParmFloatValuesFuncPtr SetParmFloatValues;
	static SetParmIntValueFuncPtr SetParmIntValue;
	static SetParmIntValuesFuncPtr SetParmIntValues;
	static SetParmNodeValueFuncPtr SetParmNodeValue;
	static SetParmStringValueFuncPtr SetParmStringValue;
	static SetPartInfoFuncPtr SetPartInfo;
	static SetPresetFuncPtr SetPreset;
	static SetServerEnvIntFuncPtr SetServerEnvInt;
	static SetServerEnvStringFuncPtr SetServerEnvString;
	static SetTimeFuncPtr SetTime;
	static SetTimelineOptionsFuncPtr SetTimelineOptions;
	static SetTransformAnimCurveFuncPtr SetTransformAnimCurve;
	static SetVertexListFuncPtr SetVertexList;
	static SetVolumeInfoFuncPtr SetVolumeInfo;
	static SetVolumeTileFloatDataFuncPtr SetVolumeTileFloatData;
	static SetVolumeTileIntDataFuncPtr SetVolumeTileIntData;
	static SetVolumeVoxelFloatDataFuncPtr SetVolumeVoxelFloatData;
	static SetVolumeVoxelIntDataFuncPtr SetVolumeVoxelIntData;
	static StartThriftNamedPipeServerFuncPtr StartThriftNamedPipeServer;
	static StartThriftSocketServerFuncPtr StartThriftSocketServer;

public:

	static HAPI_Result AddAttributeEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, const HAPI_AttributeInfo * attr_info);
	static HAPI_Result AddGroupEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_GroupType group_type, const char * group_name);
	static HAPI_Result BindCustomImplementationEmptyStub(HAPI_SessionType session_type, const char * dll_path);
	static HAPI_Result CheckForSpecificErrorsEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ErrorCodeBits errors_to_look_for, HAPI_ErrorCodeBits * errors_found);
	static HAPI_Result CleanupEmptyStub(const HAPI_Session * session);
	static HAPI_Result CloseSessionEmptyStub(const HAPI_Session * session);
	static HAPI_Result CommitGeoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id);
	static HAPI_Result ComposeChildNodeListEmptyStub(const HAPI_Session * session, HAPI_NodeId parent_node_id, HAPI_NodeTypeBits node_type_filter, HAPI_NodeFlagsBits node_flags_filter, HAPI_Bool recursive, int * count);
	static HAPI_Result ComposeNodeCookResultEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_StatusVerbosity verbosity, int * buffer_length);
	static HAPI_Result ComposeObjectListEmptyStub(const HAPI_Session * session, HAPI_NodeId parent_node_id, const char * categories, int * object_count);
	static HAPI_Result ConnectNodeInputEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, int input_index, HAPI_NodeId node_id_to_connect);
	static HAPI_Result ConvertMatrixToEulerEmptyStub(const HAPI_Session * session, const float * matrix, HAPI_RSTOrder rst_order, HAPI_XYZOrder rot_order, HAPI_TransformEuler * transform_out);
	static HAPI_Result ConvertMatrixToQuatEmptyStub(const HAPI_Session * session, const float * matrix, HAPI_RSTOrder rst_order, HAPI_Transform * transform_out);
	static HAPI_Result ConvertTransformEmptyStub(const HAPI_Session * session, const HAPI_TransformEuler * transform_in, HAPI_RSTOrder rst_order, HAPI_XYZOrder rot_order, HAPI_TransformEuler * transform_out);
	static HAPI_Result ConvertTransformEulerToMatrixEmptyStub(const HAPI_Session * session, const HAPI_TransformEuler * transform, float * matrix);
	static HAPI_Result ConvertTransformQuatToMatrixEmptyStub(const HAPI_Session * session, const HAPI_Transform * transform, float * matrix);
	static HAPI_Result CookNodeEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const HAPI_CookOptions * cook_options);
	static HAPI_Result CreateCustomSessionEmptyStub(HAPI_SessionType session_type, void * session_info, HAPI_Session * session);
	static HAPI_Result CreateInProcessSessionEmptyStub(HAPI_Session * session);
	static HAPI_Result CreateInputNodeEmptyStub(const HAPI_Session * session, HAPI_NodeId * node_id, const char * name);
	static HAPI_Result CreateNodeEmptyStub(const HAPI_Session * session, HAPI_NodeId parent_node_id, const char * operator_name, const char * node_label, HAPI_Bool cook_on_creation, HAPI_NodeId * new_node_id);
	static HAPI_Result CreateThriftNamedPipeSessionEmptyStub(HAPI_Session * session, const char * pipe_name);
	static HAPI_Result CreateThriftSocketSessionEmptyStub(HAPI_Session * session, const char * host_name, int port);
	static HAPI_Result DeleteNodeEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id);
	static HAPI_Result DisconnectNodeInputEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, int input_index);
	static HAPI_Result ExtractImageToFileEmptyStub(const HAPI_Session * session, HAPI_NodeId material_node_id, const char * image_file_format_name, const char * image_planes, const char * destination_folder_path, const char * destination_file_name, int * destination_file_path);
	static HAPI_Result ExtractImageToMemoryEmptyStub(const HAPI_Session * session, HAPI_NodeId material_node_id, const char * image_file_format_name, const char * image_planes, int * buffer_size);
	static HAPI_Result GetActiveCacheCountEmptyStub(const HAPI_Session * session, int * active_cache_count);
	static HAPI_Result GetActiveCacheNamesEmptyStub(const HAPI_Session * session, HAPI_StringHandle * cache_names_array, int active_cache_count);
	static HAPI_Result GetAssetInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_AssetInfo * asset_info);
	static HAPI_Result GetAttributeFloat64DataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, HAPI_AttributeInfo * attr_info, int stride, double * data_array, int start, int length);
	static HAPI_Result GetAttributeFloatDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, HAPI_AttributeInfo * attr_info, int stride, float * data_array, int start, int length);
	static HAPI_Result GetAttributeInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, HAPI_AttributeOwner owner, HAPI_AttributeInfo * attr_info);
	static HAPI_Result GetAttributeInt64DataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, HAPI_AttributeInfo * attr_info, int stride, HAPI_Int64 * data_array, int start, int length);
	static HAPI_Result GetAttributeIntDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, HAPI_AttributeInfo * attr_info, int stride, int * data_array, int start, int length);
	static HAPI_Result GetAttributeNamesEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_AttributeOwner owner, HAPI_StringHandle * attribute_names_array, int count);
	static HAPI_Result GetAttributeStringDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, HAPI_AttributeInfo * attr_info, HAPI_StringHandle * data_array, int start, int length);
	static HAPI_Result GetAvailableAssetCountEmptyStub(const HAPI_Session * session, HAPI_AssetLibraryId library_id, int * asset_count);
	static HAPI_Result GetAvailableAssetsEmptyStub(const HAPI_Session * session, HAPI_AssetLibraryId library_id, HAPI_StringHandle * asset_names_array, int asset_count);
	static HAPI_Result GetBoxInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId geo_node_id, HAPI_PartId part_id, HAPI_BoxInfo * box_info);
	static HAPI_Result GetCachePropertyEmptyStub(const HAPI_Session * session, const char * cache_name, HAPI_CacheProperty cache_property, int * property_value);
	static HAPI_Result GetComposedChildNodeListEmptyStub(const HAPI_Session * session, HAPI_NodeId parent_node_id, HAPI_NodeId * child_node_ids_array, int count);
	static HAPI_Result GetComposedNodeCookResultEmptyStub(const HAPI_Session * session, char * string_value, int length);
	static HAPI_Result GetComposedObjectListEmptyStub(const HAPI_Session * session, HAPI_NodeId parent_node_id, HAPI_ObjectInfo * object_infos_array, int start, int length);
	static HAPI_Result GetComposedObjectTransformsEmptyStub(const HAPI_Session * session, HAPI_NodeId parent_node_id, HAPI_RSTOrder rst_order, HAPI_Transform * transform_array, int start, int length);
	static HAPI_Result GetCookingCurrentCountEmptyStub(const HAPI_Session * session, int * count);
	static HAPI_Result GetCookingTotalCountEmptyStub(const HAPI_Session * session, int * count);
	static HAPI_Result GetCurveCountsEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int * counts_array, int start, int length);
	static HAPI_Result GetCurveInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_CurveInfo * info);
	static HAPI_Result GetCurveKnotsEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, float * knots_array, int start, int length);
	static HAPI_Result GetCurveOrdersEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int * orders_array, int start, int length);
	static HAPI_Result GetDisplayGeoInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId object_node_id, HAPI_GeoInfo * geo_info);
	static HAPI_Result GetEnvIntEmptyStub(HAPI_EnvIntType int_type, int * value);
	static HAPI_Result GetFaceCountsEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int * face_counts_array, int start, int length);
	static HAPI_Result GetFirstVolumeTileEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_VolumeTileInfo * tile);
	static HAPI_Result GetGeoInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_GeoInfo * geo_info);
	static HAPI_Result GetGeoSizeEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * format, int * size);
	static HAPI_Result GetGroupCountOnPackedInstancePartEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int * pointGroupCount, int * primitiveGroupCount);
	static HAPI_Result GetGroupMembershipEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_GroupType group_type, const char * group_name, HAPI_Bool * membership_array_all_equal, int * membership_array, int start, int length);
	static HAPI_Result GetGroupMembershipOnPackedInstancePartEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_GroupType group_type, const char * group_name, HAPI_Bool * membership_array_all_equal, int * membership_array, int start, int length);
	static HAPI_Result GetGroupNamesEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_GroupType group_type, HAPI_StringHandle * group_names_array, int group_count);
	static HAPI_Result GetGroupNamesOnPackedInstancePartEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_GroupType group_type, HAPI_StringHandle * group_names_array, int group_count);
	static HAPI_Result GetHandleBindingInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, int handle_index, HAPI_HandleBindingInfo * handle_binding_infos_array, int start, int length);
	static HAPI_Result GetHandleInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_HandleInfo * handle_infos_array, int start, int length);
	static HAPI_Result GetHeightFieldDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, float * values_array, int start, int length);
	static HAPI_Result GetImageInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId material_node_id, HAPI_ImageInfo * image_info);
	static HAPI_Result GetImageMemoryBufferEmptyStub(const HAPI_Session * session, HAPI_NodeId material_node_id, char * buffer, int length);
	static HAPI_Result GetImagePlaneCountEmptyStub(const HAPI_Session * session, HAPI_NodeId material_node_id, int * image_plane_count);
	static HAPI_Result GetImagePlanesEmptyStub(const HAPI_Session * session, HAPI_NodeId material_node_id, HAPI_StringHandle * image_planes_array, int image_plane_count);
	static HAPI_Result GetInstanceTransformsEmptyStub(const HAPI_Session * session, HAPI_NodeId object_node_id, HAPI_RSTOrder rst_order, HAPI_Transform * transforms_array, int start, int length);
	static HAPI_Result GetInstancedObjectIdsEmptyStub(const HAPI_Session * session, HAPI_NodeId object_node_id, HAPI_NodeId * instanced_node_id_array, int start, int length);
	static HAPI_Result GetInstancedPartIdsEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_PartId * instanced_parts_array, int start, int length);
	static HAPI_Result GetInstancerPartTransformsEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_RSTOrder rst_order, HAPI_Transform * transforms_array, int start, int length);
	static HAPI_Result GetManagerNodeIdEmptyStub(const HAPI_Session * session, HAPI_NodeType node_type, HAPI_NodeId * node_id);
	static HAPI_Result GetMaterialInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId material_node_id, HAPI_MaterialInfo * material_info);
	static HAPI_Result GetMaterialNodeIdsOnFacesEmptyStub(const HAPI_Session * session, HAPI_NodeId geometry_node_id, HAPI_PartId part_id, HAPI_Bool * are_all_the_same, HAPI_NodeId * material_ids_array, int start, int length);
	static HAPI_Result GetNextVolumeTileEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_VolumeTileInfo * tile);
	static HAPI_Result GetNodeInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_NodeInfo * node_info);
	static HAPI_Result GetNodeInputNameEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, int input_idx, HAPI_StringHandle * name);
	static HAPI_Result GetNodePathEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_NodeId relative_to_node_id, HAPI_StringHandle * path);
	static HAPI_Result GetObjectInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ObjectInfo * object_info);
	static HAPI_Result GetObjectTransformEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_NodeId relative_to_node_id, HAPI_RSTOrder rst_order, HAPI_Transform * transform);
	static HAPI_Result GetParametersEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmInfo * parm_infos_array, int start, int length);
	static HAPI_Result GetParmChoiceListsEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmChoiceInfo *parm_choices_array, int start, int length);
	static HAPI_Result GetParmFileEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, const char * destination_directory, const char * destination_file_name);
	static HAPI_Result GetParmFloatValueEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, int index, float * value);
	static HAPI_Result GetParmFloatValuesEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, float * values_array, int start, int length);
	static HAPI_Result GetParmIdFromNameEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, HAPI_ParmId * parm_id);
	static HAPI_Result GetParmInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmId parm_id, HAPI_ParmInfo * parm_info);
	static HAPI_Result GetParmInfoFromNameEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, HAPI_ParmInfo * parm_info);
	static HAPI_Result GetParmIntValueEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, int index, int * value);
	static HAPI_Result GetParmIntValuesEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, int * values_array, int start, int length);
	static HAPI_Result GetParmNodeValueEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, HAPI_NodeId * value);
	static HAPI_Result GetParmStringValueEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, int index, HAPI_Bool evaluate, HAPI_StringHandle * value);
	static HAPI_Result GetParmStringValuesEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_Bool evaluate, HAPI_StringHandle * values_array, int start, int length);
	static HAPI_Result GetParmTagNameEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmId parm_id, int tag_index, HAPI_StringHandle * tag_name);
	static HAPI_Result GetParmTagValueEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmId parm_id, const char * tag_name, HAPI_StringHandle * tag_value);
	static HAPI_Result GetParmWithTagEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * tag_name, HAPI_ParmId * parm_id);
	static HAPI_Result GetPartInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_PartInfo * part_info);
	static HAPI_Result GetPresetEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, char * buffer, int buffer_length);
	static HAPI_Result GetPresetBufLengthEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PresetType preset_type, const char * preset_name, int * buffer_length);
	static HAPI_Result GetServerEnvIntEmptyStub(const HAPI_Session * session, const char * variable_name, int * value);
	static HAPI_Result GetServerEnvStringEmptyStub(const HAPI_Session * session, const char * variable_name, HAPI_StringHandle * value);
	static HAPI_Result GetSessionEnvIntEmptyStub(const HAPI_Session * session, HAPI_SessionEnvIntType int_type, int * value);
	static HAPI_Result GetSphereInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId geo_node_id, HAPI_PartId part_id, HAPI_SphereInfo * sphere_info);
	static HAPI_Result GetStatusEmptyStub(const HAPI_Session * session, HAPI_StatusType status_type, int * status);
	static HAPI_Result GetStatusStringEmptyStub(const HAPI_Session * session, HAPI_StatusType status_type, char * string_value, int length);
	static HAPI_Result GetStatusStringBufLengthEmptyStub(const HAPI_Session * session, HAPI_StatusType status_type, HAPI_StatusVerbosity verbosity, int * buffer_length);
	static HAPI_Result GetStringEmptyStub(const HAPI_Session * session, HAPI_StringHandle string_handle, char * string_value, int length);
	static HAPI_Result GetStringBufLengthEmptyStub(const HAPI_Session * session, HAPI_StringHandle string_handle, int * buffer_length);
	static HAPI_Result GetSupportedImageFileFormatCountEmptyStub(const HAPI_Session * session, int * file_format_count);
	static HAPI_Result GetSupportedImageFileFormatsEmptyStub(const HAPI_Session * session, HAPI_ImageFileFormat * formats_array, int file_format_count);
	static HAPI_Result GetTimeEmptyStub(const HAPI_Session * session, float * time);
	static HAPI_Result GetTimelineOptionsEmptyStub(const HAPI_Session * session, HAPI_TimelineOptions * timeline_options);
	static HAPI_Result GetVertexListEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int * vertex_list_array, int start, int length);
	static HAPI_Result GetVolumeBoundsEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, float * x_min, float * y_min, float * z_min, float * x_max, float * y_max, float * z_max, float * x_center, float * y_center, float * z_center);
	static HAPI_Result GetVolumeInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_VolumeInfo * volume_info);
	static HAPI_Result GetVolumeTileFloatDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, float fill_value, const HAPI_VolumeTileInfo * tile, float * values_array, int length);
	static HAPI_Result GetVolumeTileIntDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int fill_value, const HAPI_VolumeTileInfo * tile, int * values_array, int length);
	static HAPI_Result GetVolumeVoxelFloatDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int x_index, int y_index, int z_index, float * values_array, int value_count);
	static HAPI_Result GetVolumeVoxelIntDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int x_index, int y_index, int z_index, int * values_array, int value_count);
	static HAPI_Result InitializeEmptyStub(const HAPI_Session * session, const HAPI_CookOptions * cook_options, HAPI_Bool use_cooking_thread, int cooking_thread_stack_size, const char * houdini_environment_files, const char * otl_search_path, const char * dso_search_path, const char * image_dso_search_path, const char * audio_dso_search_path);
	static HAPI_Result InsertMultiparmInstanceEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmId parm_id, int instance_position);
	static HAPI_Result InterruptEmptyStub(const HAPI_Session * session);
	static HAPI_Result IsInitializedEmptyStub(const HAPI_Session * session);
	static HAPI_Result IsNodeValidEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, int unique_node_id, HAPI_Bool * answer);
	static HAPI_Result IsSessionValidEmptyStub(const HAPI_Session * session);
	static HAPI_Result LoadAssetLibraryFromFileEmptyStub(const HAPI_Session * session, const char * file_path, HAPI_Bool allow_overwrite, HAPI_AssetLibraryId* library_id);
	static HAPI_Result LoadAssetLibraryFromMemoryEmptyStub(const HAPI_Session * session, const char * library_buffer, int library_buffer_length, HAPI_Bool allow_overwrite, HAPI_AssetLibraryId * library_id);
	static HAPI_Result LoadGeoFromFileEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * file_name);
	static HAPI_Result LoadGeoFromMemoryEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * format, const char * buffer, int length);
	static HAPI_Result LoadHIPFileEmptyStub(const HAPI_Session * session, const char * file_name, HAPI_Bool cook_on_load);
	static HAPI_Result ParmHasTagEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmId parm_id, const char * tag_name, HAPI_Bool * has_tag);
	static HAPI_Result PythonThreadInterpreterLockEmptyStub(const HAPI_Session * session, HAPI_Bool locked);
	static HAPI_Result QueryNodeInputEmptyStub(const HAPI_Session * session, HAPI_NodeId node_to_query, int input_index, HAPI_NodeId * connected_node_id);
	static HAPI_Result RemoveMultiparmInstanceEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmId parm_id, int instance_position);
	static HAPI_Result RenameNodeEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * new_name);
	static HAPI_Result RenderCOPToImageEmptyStub(const HAPI_Session * session, HAPI_NodeId cop_node_id);
	static HAPI_Result RenderTextureToImageEmptyStub(const HAPI_Session * session, HAPI_NodeId material_node_id, HAPI_ParmId parm_id);
	static HAPI_Result ResetSimulationEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id);
	static HAPI_Result RevertGeoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id);
	static HAPI_Result SaveGeoToFileEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * file_name);
	static HAPI_Result SaveGeoToMemoryEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, char * buffer, int length);
	static HAPI_Result SaveHIPFileEmptyStub(const HAPI_Session * session, const char * file_path, HAPI_Bool lock_nodes);
	static HAPI_Result SetAnimCurveEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_ParmId parm_id, int parm_index, const HAPI_Keyframe * curve_keyframes_array, int keyframe_count);
	static HAPI_Result SetAttributeFloat64DataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, const HAPI_AttributeInfo * attr_info, const double * data_array, int start, int length);
	static HAPI_Result SetAttributeFloatDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, const HAPI_AttributeInfo * attr_info, const float * data_array, int start, int length);
	static HAPI_Result SetAttributeInt64DataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, const HAPI_AttributeInfo * attr_info, const HAPI_Int64 * data_array, int start, int length);
	static HAPI_Result SetAttributeIntDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, const HAPI_AttributeInfo * attr_info, const int * data_array, int start, int length);
	static HAPI_Result SetAttributeStringDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, const HAPI_AttributeInfo *attr_info, const char ** data_array, int start, int length);
	static HAPI_Result SetCachePropertyEmptyStub(const HAPI_Session * session, const char * cache_name, HAPI_CacheProperty cache_property, int property_value);
	static HAPI_Result SetCurveCountsEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const int * counts_array, int start, int length);
	static HAPI_Result SetCurveInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const HAPI_CurveInfo * info);
	static HAPI_Result SetCurveKnotsEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const float * knots_array, int start, int length);
	static HAPI_Result SetCurveOrdersEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const int * orders_array, int start, int length);
	static HAPI_Result SetFaceCountsEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const int * face_counts_array, int start, int length);
	static HAPI_Result SetGroupMembershipEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, HAPI_GroupType group_type, const char * group_name, const int * membership_array, int start, int length);
	static HAPI_Result SetHeightFieldDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const char * name, const float * values_array, int start, int length);
	static HAPI_Result SetImageInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId material_node_id, const HAPI_ImageInfo * image_info);
	static HAPI_Result SetObjectTransformEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const HAPI_TransformEuler * trans);
	static HAPI_Result SetParmFloatValueEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, int index, float value);
	static HAPI_Result SetParmFloatValuesEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const float * values_array, int start, int length);
	static HAPI_Result SetParmIntValueEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, int index, int value);
	static HAPI_Result SetParmIntValuesEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const int * values_array, int start, int length);
	static HAPI_Result SetParmNodeValueEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * parm_name, HAPI_NodeId value);
	static HAPI_Result SetParmStringValueEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, const char * value, HAPI_ParmId parm_id, int index);
	static HAPI_Result SetPartInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const HAPI_PartInfo * part_info);
	static HAPI_Result SetPresetEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PresetType preset_type, const char * preset_name, const char * buffer, int buffer_length);
	static HAPI_Result SetServerEnvIntEmptyStub(const HAPI_Session * session, const char * variable_name, int value);
	static HAPI_Result SetServerEnvStringEmptyStub(const HAPI_Session * session, const char * variable_name, const char * value);
	static HAPI_Result SetTimeEmptyStub(const HAPI_Session * session, float time);
	static HAPI_Result SetTimelineOptionsEmptyStub(const HAPI_Session * session, const HAPI_TimelineOptions * timeline_options);
	static HAPI_Result SetTransformAnimCurveEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_TransformComponent trans_comp, const HAPI_Keyframe * curve_keyframes_array, int keyframe_count);
	static HAPI_Result SetVertexListEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const int * vertex_list_array, int start, int length);
	static HAPI_Result SetVolumeInfoEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const HAPI_VolumeInfo * volume_info);
	static HAPI_Result SetVolumeTileFloatDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const HAPI_VolumeTileInfo * tile, const float * values_array, int length);
	static HAPI_Result SetVolumeTileIntDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, const HAPI_VolumeTileInfo * tile, const int * values_array, int length);
	static HAPI_Result SetVolumeVoxelFloatDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int x_index, int y_index, int z_index, const float * values_array, int value_count);
	static HAPI_Result SetVolumeVoxelIntDataEmptyStub(const HAPI_Session * session, HAPI_NodeId node_id, HAPI_PartId part_id, int x_index, int y_index, int z_index, const int * values_array, int value_count);
	static HAPI_Result StartThriftNamedPipeServerEmptyStub(const HAPI_ThriftServerOptions * options, const char * pipe_name, HAPI_ProcessId * process_id);
	static HAPI_Result StartThriftSocketServerEmptyStub(const HAPI_ThriftServerOptions * options, int port, HAPI_ProcessId * process_id);
};
