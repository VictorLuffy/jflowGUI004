#include "gfx/libaria/inc/libaria_widget_line_graph.h"
#include "jflo_widget_line_graph.h"

#if JFLO_LINE_GRAPH_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define DEFAULT_WIDTH           101
#define DEFAULT_HEIGHT          101

#define DEFAULT_TICK_LENGTH     5
#define DEFAULT_TICK_INTERVAL   10
#define DEFAULT_SUBTICK_INTERVAL   5
#define DEFAULT_MAX_VALUE       100
#define DEFAULT_MIN_VALUE       0

#define DEFAULT_POINT_SIZE      10

void _jfloLineGraphWidget_Constructor(jfloLineGraphWidget* graph)
{
    _laWidget_Constructor((laWidget*)graph);

    graph->widget.type = LA_WIDGET_ARC;
    
    graph->widget.destructor = (laWidget_Destructor_FnPtr)&_jfloLineGraphWidget_Destructor;

    // override base class methods
    graph->widget.paint = (laWidget_Paint_FnPtr)&_jfloLineGraphWidget_Paint;

    graph->widget.rect.width = DEFAULT_WIDTH;
    graph->widget.rect.height = DEFAULT_HEIGHT;

    graph->widget.borderType = LA_WIDGET_BORDER_NONE;
    graph->widget.backgroundType = LA_WIDGET_BACKGROUND_NONE;
    
    graph->tickLength = DEFAULT_TICK_LENGTH;
    graph->fillGraphArea = LA_TRUE;
    graph->fillValueArea = LA_TRUE;
    graph->stacked = LA_FALSE;
    
    graph->maxValue = DEFAULT_MAX_VALUE;
    graph->minValue = DEFAULT_MIN_VALUE;
    graph->tickInterval = DEFAULT_TICK_INTERVAL;
    graph->subtickInterval = DEFAULT_SUBTICK_INTERVAL;
    
    graph->valueGridlinesVisible = LA_TRUE;
    graph->valueAxisLabelsVisible = LA_TRUE;
    graph->valueAxisTicksVisible = LA_TRUE;
    graph->valueAxisSubticksVisible = LA_TRUE;
    graph->valueAxisTicksPosition = LINE_GRAPH_TICK_CENTER;
    graph->valueAxisSubticksPosition = LINE_GRAPH_TICK_CENTER;
    
    graph->categAxisLabelsVisible = LA_TRUE;
    graph->categAxisTicksVisible = LA_TRUE;
    graph->categAxisTicksPosition = LINE_GRAPH_TICK_CENTER;
    
    laArray_Create(&graph->dataSeries);
    laArray_Create(&graph->categories);
}

void _jfloLineGraphWidget_Destructor(jfloLineGraphWidget* graph)
{
    jfloLineGraphWidget_DestroyAll(graph);
    
    _laWidget_Destructor((laWidget*)graph);
}

jfloLineGraphWidget* jfloLineGraphWidget_New()
{
    jfloLineGraphWidget* graph = NULL;

    if(laContext_GetActive() == NULL)
        return NULL;

    graph = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(jfloLineGraphWidget));

    if(graph == NULL)
        return NULL;
    
    _jfloLineGraphWidget_Constructor(graph);

    return graph;
}

uint32_t jfloLineGraphWidget_GetTickLength(jfloLineGraphWidget* graph)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->tickLength;
}

laResult jfloLineGraphWidget_SetTickLength(jfloLineGraphWidget* graph, uint32_t length)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->tickLength == length)
        return LA_SUCCESS;
        
    graph->tickLength = length;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

laBool jfloLineGraphWidget_GetStacked(jfloLineGraphWidget* graph)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->stacked;
}

laResult jfloLineGraphWidget_SetStacked(jfloLineGraphWidget* graph, laBool stacked)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->stacked == stacked)
        return LA_SUCCESS;
        
    graph->stacked = stacked;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

uint32_t jfloLineGraphWidget_GetMaxValue(jfloLineGraphWidget* graph, laLineGraphValueAxis axis)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->maxValue;
}

laResult jfloLineGraphWidget_SetMaxValue(jfloLineGraphWidget* graph, laLineGraphValueAxis axis, int32_t value)
{
    if(graph == NULL)
        return LA_FAILURE;

    if (value <= graph->minValue)
        return LA_FAILURE;
    
    if(graph->maxValue == value)
        return LA_SUCCESS;
        
    graph->maxValue = value;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

uint32_t jfloLineGraphWidget_GetMinValue(jfloLineGraphWidget* graph, laLineGraphValueAxis axis)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->minValue;
}

laResult jfloLineGraphWidget_SetMinValue(jfloLineGraphWidget* graph, laLineGraphValueAxis axis, int32_t value)
{
    if(graph == NULL)
        return LA_FAILURE;
    
    if (value >= graph->maxValue)
        return LA_FAILURE;

    if(graph->minValue == value)
        return LA_SUCCESS;
        
    graph->minValue = value;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

laBool jfloLineGraphWidget_GetValueAxisLabelsVisible(jfloLineGraphWidget* graph, laLineGraphValueAxis axis)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->valueAxisLabelsVisible;
}

laResult jfloLineGraphWidget_SetValueAxisLabelsVisible(jfloLineGraphWidget* graph, laLineGraphValueAxis axis, laBool visible)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->valueAxisLabelsVisible == visible)
        return LA_SUCCESS;
        
    graph->valueAxisLabelsVisible = visible;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

laBool jfloLineGraphWidget_GetFillGraphArea(jfloLineGraphWidget* graph)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->fillGraphArea;
}

laResult jfloLineGraphWidget_SetFillGraphArea(jfloLineGraphWidget* graph, laBool fill)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->fillGraphArea == fill)
        return LA_SUCCESS;
        
    graph->fillGraphArea = fill;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

laBool jfloLineGraphWidget_GetFillSeriesArea(jfloLineGraphWidget* graph)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->fillValueArea;
}

laResult jfloLineGraphWidget_SetFillSeriesArea(jfloLineGraphWidget* graph, laBool fill)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->fillValueArea == fill)
        return LA_SUCCESS;
        
    graph->fillValueArea = fill;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}


laBool jfloLineGraphWidget_GetGridlinesVisible(jfloLineGraphWidget* graph, laLineGraphValueAxis axis)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->valueGridlinesVisible;
}

laResult jfloLineGraphWidget_SetGridlinesVisible(jfloLineGraphWidget* graph, laLineGraphValueAxis axis, laBool visible)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->valueGridlinesVisible == visible)
        return LA_SUCCESS;
        
    graph->valueGridlinesVisible = visible;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

laBool jfloLineGraphWidget_GetValueAxisTicksVisible(jfloLineGraphWidget* graph, laLineGraphValueAxis axis)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->valueAxisTicksVisible;
}

laResult jfloLineGraphWidget_SetValueAxisTicksVisible(jfloLineGraphWidget* graph, laLineGraphValueAxis axis, laBool visible)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->valueAxisTicksVisible == visible)
        return LA_SUCCESS;
        
    graph->valueAxisTicksVisible = visible;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

uint32_t jfloLineGraphWidget_GetValueAxisTickInterval(jfloLineGraphWidget* graph, laLineGraphValueAxis axis)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->tickInterval;
}

laResult jfloLineGraphWidget_SetValueAxisTickInterval(jfloLineGraphWidget* graph, laLineGraphValueAxis axis, uint32_t interval)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->tickInterval == interval)
        return LA_SUCCESS;
        
    graph->tickInterval = interval;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

uint32_t jfloLineGraphWidget_GetValueAxisSubtickInterval(jfloLineGraphWidget* graph, laLineGraphValueAxis axis)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->subtickInterval;
}

laResult jfloLineGraphWidget_SetValueAxisSubtickInterval(jfloLineGraphWidget* graph, laLineGraphValueAxis axis, uint32_t interval)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->subtickInterval == interval)
        return LA_SUCCESS;
        
    graph->subtickInterval = interval;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

laBool jfloLineGraphWidget_GetValueAxisSubticksVisible(jfloLineGraphWidget* graph, laLineGraphValueAxis axis)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->valueAxisSubticksVisible;
}

laResult jfloLineGraphWidget_SetValueAxisSubticksVisible(jfloLineGraphWidget* graph, laLineGraphValueAxis axis, laBool visible)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->valueAxisSubticksVisible == visible)
        return LA_SUCCESS;
        
    graph->valueAxisSubticksVisible = visible;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

laBool jfloLineGraphWidget_GetCategoryAxisTicksVisible(jfloLineGraphWidget* graph)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->categAxisTicksVisible;
}

laResult jfloLineGraphWidget_SetCategoryAxisTicksVisible(jfloLineGraphWidget* graph, laBool visible)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->categAxisTicksVisible == visible)
        return LA_SUCCESS;
        
    graph->categAxisTicksVisible = visible;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

laResult jfloLineGraphWidget_AddCategory(jfloLineGraphWidget* graph, uint32_t * id)
{
    jfloLineGraphCategory * category;
    
    if (graph == NULL)
        return LA_FAILURE;
    
    category = laContext_GetActive()->memIntf.heap.malloc(sizeof(jfloLineGraphCategory));
    if (category == NULL)
        return LA_FAILURE;
    
    laString_Initialize(&category->text);
    
    laArray_PushBack(&graph->categories, category);
    
    if (id != NULL)
    {
        *id = graph->categories.size;
    }
    
    laWidget_Invalidate((laWidget*)graph);
    
    return LA_SUCCESS;
}

laResult jfloLineGraphWidget_GetCategoryText(jfloLineGraphWidget* graph, uint32_t categoryID, laString * str)
{
    jfloLineGraphCategory * category;
    
    if(graph == NULL)
        return LA_FAILURE;
    
    if (categoryID >= graph->categories.size)
        return LA_FAILURE;
    
    category = laArray_Get(&graph->categories, categoryID);
    if (category == NULL)
        return LA_FAILURE;
    
    return laString_Copy(str, &category->text);
}

laResult jfloLineGraphWidget_SetCategoryText(jfloLineGraphWidget* graph, int32_t categoryID, laString str)
{
    jfloLineGraphCategory * category;
    
    if(graph == NULL)
        return LA_FAILURE;
    
    if (categoryID >= (int32_t) graph->categories.size)
        return LA_FAILURE;
    
    if (categoryID < 0)
        categoryID = graph->categories.size - 1;
    
    category = laArray_Get(&graph->categories, categoryID);
    if (category == NULL)
        return LA_FAILURE;
    
    if(laString_Copy(&category->text, &str) == LA_FAILURE)
        return LA_FAILURE;
    
    laWidget_Invalidate((laWidget*)graph);
    
    return LA_SUCCESS;
}

laResult jfloLineGraphWidget_AddSeries(jfloLineGraphWidget* graph, uint32_t * seriesID)
{
    jfloLineGraphDataSeries * series;
    
    if (graph == NULL)
        return LA_FAILURE;
    
    series = laContext_GetActive()->memIntf.heap.malloc(sizeof(jfloLineGraphDataSeries));
    if (series == NULL)
        return LA_FAILURE;

    laArray_Create(&series->data);
    series->axis = LINE_GRAPH_AXIS_0;
    series->scheme = graph->widget.scheme;
    series->drawLines = LA_TRUE;
    series->pointType = LINE_GRAPH_DATA_POINT_CIRCLE;
    series->fillPoints = LA_TRUE;
    series->pointSize = DEFAULT_POINT_SIZE;
    
    laArray_PushBack(&graph->dataSeries, series);
    
    if (seriesID != NULL)
    {
        *seriesID = graph->dataSeries.size;
    }
    
    laWidget_Invalidate((laWidget*)graph);
    
    return LA_SUCCESS;
}

laResult jfloLineGraphWidget_AddDataToSeries(jfloLineGraphWidget* graph, uint32_t seriesID, int32_t value, uint32_t * index)
{
    jfloLineGraphDataSeries * series;
    int32_t * data;
    
    if (graph == NULL)
        return LA_FAILURE;
    
    if (seriesID >= graph->dataSeries.size)
        return LA_FAILURE;
    
    data = laContext_GetActive()->memIntf.heap.malloc(sizeof(data));
    
    *data = value;
    
    series = laArray_Get(&graph->dataSeries, seriesID);
    
    laArray_PushBack(&series->data, data);

    if (index != NULL)
    {
       *index = series->data.size - 1;
    }
    
    laWidget_Invalidate((laWidget*)graph);
    
    return LA_SUCCESS;
}

laResult jfloLineGraphWidget_ClearPlottingArea(jfloLineGraphWidget* graph)
{
    graph->clearPlottingArea = true;
    
    laWidget_Invalidate((laWidget*)graph);
    
    return LA_SUCCESS;
}

laResult jfloLineGraphWidget_SetDataInSeries(jfloLineGraphWidget* graph, 
                                          uint32_t seriesID,
                                          uint32_t index,
                                          int32_t value)
{
    jfloLineGraphDataSeries * series;
    int32_t * data;

    
    // Custom
    graph->indexNextValueToDraw = index;
    index = index % 20;
    
    
    if (graph == NULL)
        return LA_FAILURE;
    
    if (seriesID >= graph->dataSeries.size)
        return LA_FAILURE;
    
    series = laArray_Get(&graph->dataSeries, seriesID);

    if (index >= series->data.size)
        return LA_FAILURE;
    
    data = laArray_Get(&series->data, index);
    
    *data = value;
    
    laWidget_Invalidate((laWidget*)graph);
    
    return LA_SUCCESS;
}

laScheme * jfloLineGraphWidget_GetSeriesScheme(jfloLineGraphWidget* graph, uint32_t seriesID)
{
    jfloLineGraphDataSeries * series;
    
    if(graph == NULL)
        return NULL;
    
    if (seriesID >= graph->dataSeries.size)
        return NULL;
    
    series = laArray_Get(&graph->dataSeries, seriesID);
    if (series == NULL)
        return NULL;
    
    return series->scheme;
}

laResult jfloLineGraphWidget_SetSeriesScheme(jfloLineGraphWidget* graph, int32_t seriesID, laScheme * scheme)
{
    jfloLineGraphDataSeries * series;
    
    if(graph == NULL || scheme == NULL)
        return LA_FAILURE;
    
    if (seriesID >= (int32_t) graph->dataSeries.size)
        return LA_FAILURE;
    
    if (seriesID < 0)
        seriesID = graph->dataSeries.size - 1;
    
    series = laArray_Get(&graph->dataSeries, seriesID);
    if (series == NULL)
        return LA_FAILURE;
    
    series->scheme = scheme;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

laBool jfloLineGraphWidget_GetSeriesFillPoints(jfloLineGraphWidget* graph, uint32_t seriesID)
{
    jfloLineGraphDataSeries * series;
    
    if(graph == NULL)
        return LA_FALSE;
    
    if (seriesID >= graph->dataSeries.size)
        return LA_FALSE;
    
    series = laArray_Get(&graph->dataSeries, seriesID);
    if (series == NULL)
        return LA_FALSE;
    
    return series->fillPoints;
}

laResult jfloLineGraphWidget_SetSeriesFillPoints(jfloLineGraphWidget* graph, int32_t seriesID, laBool fill)
{
    jfloLineGraphDataSeries * series;
    
    if(graph == NULL)
        return LA_FAILURE;
    
    if (seriesID >= (int32_t) graph->dataSeries.size)
        return LA_FAILURE;
    
    if (seriesID < 0)
        seriesID = graph->dataSeries.size - 1;
    
    series = laArray_Get(&graph->dataSeries, seriesID);
    if (series == NULL)
        return LA_FAILURE;
    
    series->fillPoints = fill;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

laBool jfloLineGraphWidget_GetSeriesLinesVisible(jfloLineGraphWidget* graph, uint32_t seriesID)
{
    jfloLineGraphDataSeries * series;
    
    if(graph == NULL)
        return LA_FALSE;
    
    if (seriesID >= graph->dataSeries.size)
        return LA_FALSE;
    
    series = laArray_Get(&graph->dataSeries, seriesID);
    if (series == NULL)
        return LA_FALSE;
    
    return series->drawLines;
}

laResult jfloLineGraphWidget_SetSeriesLinesVisible(jfloLineGraphWidget* graph, int32_t seriesID, laBool visible)
{
    jfloLineGraphDataSeries * series;
    
    if(graph == NULL)
        return LA_FAILURE;
    
    if (seriesID >= (int32_t) graph->dataSeries.size)
        return LA_FAILURE;
    
    if (seriesID < 0)
        seriesID = graph->dataSeries.size - 1;
    
    series = laArray_Get(&graph->dataSeries, seriesID);
    if (series == NULL)
        return LA_FAILURE;
    
    series->drawLines = visible;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

laLineGraphDataPointType jfloLineGraphWidget_GetSeriesPointType(jfloLineGraphWidget* graph, uint32_t seriesID)
{
    jfloLineGraphDataSeries * series;
    
    if(graph == NULL)
        return LINE_GRAPH_DATA_POINT_NONE;
    
    if (seriesID >= graph->dataSeries.size)
        return LINE_GRAPH_DATA_POINT_NONE;
    
    series = laArray_Get(&graph->dataSeries, seriesID);
    if (series == NULL)
        return LINE_GRAPH_DATA_POINT_NONE;
    
    return series->pointType;
}

laResult jfloLineGraphWidget_SetSeriesPointType(jfloLineGraphWidget* graph, int32_t seriesID, laLineGraphDataPointType type)
{
    jfloLineGraphDataSeries * series;
    
    if(graph == NULL)
        return LA_FAILURE;
    
    if (seriesID >= (int32_t) graph->dataSeries.size)
        return LA_FAILURE;
    
    if (seriesID < 0)
        seriesID = graph->dataSeries.size - 1;
    
    series = laArray_Get(&graph->dataSeries, seriesID);
    if (series == NULL)
        return LA_FAILURE;
    
    series->pointType = type;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

uint32_t jfloLineGraphWidget_GetSeriesPointSize(jfloLineGraphWidget* graph, uint32_t seriesID)
{
    jfloLineGraphDataSeries * series;
    
    if(graph == NULL)
        return 0;
    
    if (seriesID >= graph->dataSeries.size)
        return 0;
    
    series = laArray_Get(&graph->dataSeries, seriesID);
    if (series == NULL)
        return 0;
    
    return series->pointSize;
}

laResult jfloLineGraphWidget_SetSeriesPointSize(jfloLineGraphWidget* graph, int32_t seriesID, uint32_t size)
{
    jfloLineGraphDataSeries * series;
    
    if(graph == NULL)
        return LA_FAILURE;
    
    if (seriesID >= (int32_t) graph->dataSeries.size)
        return LA_FAILURE;
    
    if (seriesID < 0)
        seriesID = graph->dataSeries.size - 1;
    
    series = laArray_Get(&graph->dataSeries, seriesID);
    if (series == NULL)
        return LA_FAILURE;
    
    series->pointSize = size;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

laResult jfloLineGraphWidget_DestroyAll(jfloLineGraphWidget* graph)
{
    jfloLineGraphCategory * category;
    jfloLineGraphDataSeries * series;
    uint32_t i;
    
    if (graph == NULL)
        return LA_FAILURE;
    
    // Free category string data
    for (i = 0; i < graph->categories.size; i++)
    {
        category = laArray_Get(&graph->categories, i);
        laString_Destroy(&category->text);
    }

    //Free the category array and contents
    laArray_Destroy(&graph->categories);
    
    // Free category string data
    for (i = 0; i < graph->dataSeries.size; i++)
    {
        series = laArray_Get(&graph->dataSeries, i);
        if (series != NULL)
        {
            //Destroy the data list and containers
            laArray_Destroy(&series->data);
             //Destroy the pointer list
            laArray_Destroy(&series->data);
        }
    }
    
    laArray_Destroy(&graph->dataSeries);
    
    laWidget_Invalidate((laWidget*)graph);
    
    return LA_SUCCESS;
}

laResult jfloLineGraphWidget_SetStringTable(jfloLineGraphWidget* graph, 
                                         GFXU_StringTableAsset * stringTable)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->stringTable == stringTable)
        return LA_SUCCESS;
        
    graph->stringTable = stringTable;
    
    laWidget_Invalidate((laWidget*) graph);
        
    return LA_SUCCESS;
}

laResult jfloLineGraphWidget_SetTicksLabelsStringID(jfloLineGraphWidget* graph, 
                                                 uint32_t stringID)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->ticksLabelsStringID == stringID)
        return LA_SUCCESS;
        
    graph->ticksLabelsStringID = stringID;
    
    laWidget_Invalidate((laWidget*) graph);
        
    return LA_SUCCESS;
}

laBool jfloLineGraphWidget_GetCategoryAxisLabelsVisible(jfloLineGraphWidget* graph)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->categAxisLabelsVisible;
}

laResult jfloLineGraphWidget_SetCategoryAxisLabelsVisible(jfloLineGraphWidget* graph, laBool visible)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->categAxisLabelsVisible == visible)
        return LA_SUCCESS;
        
    graph->categAxisLabelsVisible = visible;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;
}

laLineGraphTickPosition jfloLineGraphWidget_GetValueAxisTicksPosition(jfloLineGraphWidget* graph, laLineGraphValueAxis axis)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->valueAxisTicksPosition;
}
laResult jfloLineGraphWidget_SetValueAxisTicksPosition(jfloLineGraphWidget* graph, laLineGraphValueAxis axis, laLineGraphTickPosition position)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->valueAxisTicksPosition == position)
        return LA_SUCCESS;
        
    graph->valueAxisTicksPosition = position;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS; 
}

laLineGraphTickPosition jfloLineGraphWidget_GetValueAxisSubticksPosition(jfloLineGraphWidget* graph, laLineGraphValueAxis axis)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->valueAxisSubticksPosition;
}

laResult jfloLineGraphWidget_SetValueAxisSubticksPosition(jfloLineGraphWidget* graph, laLineGraphValueAxis axis, laLineGraphTickPosition position)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->valueAxisSubticksPosition == position)
        return LA_SUCCESS;
        
    graph->valueAxisSubticksPosition = position;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;     
}

laLineGraphTickPosition jfloLineGraphWidget_GetCategoryAxisTicksPosition(jfloLineGraphWidget* graph)

{
    if(graph == NULL)
        return LA_FAILURE;
        
    return graph->categAxisTicksPosition;
}

laResult jfloLineGraphWidget_SetCategoryAxisTicksPosition(jfloLineGraphWidget* graph, laLineGraphTickPosition position)
{
    if(graph == NULL)
        return LA_FAILURE;
        
    if(graph->categAxisTicksPosition == position)
        return LA_SUCCESS;
        
    graph->categAxisTicksPosition = position;
    
    laWidget_Invalidate((laWidget*)graph);
        
    return LA_SUCCESS;      
}




#endif // LA_LINE_GRAPH_WIDGET_ENABLED