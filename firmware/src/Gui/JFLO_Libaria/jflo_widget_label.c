#include "gfx/libaria/inc/libaria_widget_label.h"
#include "jflo_widget_label.h"

#if JFLO_LABEL_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_layer.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define DEFAULT_WIDTH           100
#define DEFAULT_HEIGHT          25

static void invalidateTextRect(jfloLabelWidget* lbl)
{
    GFX_Rect textRect, drawRect;
    
    _jfloLabelWidget_GetTextRect(lbl, &textRect, &drawRect);
    
    laLayer_AddDamageRect(laUtils_GetLayer((laWidget*)lbl),
		                  &drawRect,
					      LA_FALSE);
}

static void languageChanging(jfloLabelWidget* lbl)
{
    if(laString_IsEmpty(&lbl->text) == LA_FALSE)
        laWidget_Invalidate((laWidget*)lbl);
}

void _jfloLabelWidget_Constructor(jfloLabelWidget* lbl)
{
    _laWidget_Constructor((laWidget*)lbl);
    
    lbl->widget.destructor = (laWidget_Destructor_FnPtr)&_jfloLabelWidget_Destructor;
    
    lbl->widget.languageChangeEvent = (laWidget_LanguageChangingEvent_FnPtr)&languageChanging;

    lbl->widget.type = LA_WIDGET_LABEL;

    // override base class methods
    lbl->widget.paint = (laWidget_Paint_FnPtr)&_jfloLabelWidget_Paint;

    lbl->widget.rect.width = DEFAULT_WIDTH;
    lbl->widget.rect.height = DEFAULT_HEIGHT;

    lbl->widget.borderType = LA_WIDGET_BORDER_NONE;

    laString_Initialize(&lbl->text);
    
    lbl->halign = LA_HALIGN_CENTER;
    lbl->valign = LA_VALIGN_MIDDLE;
}

void _jfloLabelWidget_Destructor(jfloLabelWidget* lbl)
{
    laString_Destroy(&lbl->text);
    
    // free any existing memory reader
    if(lbl->reader != NULL)
    {
        laContext_GetActive()->memIntf.heap.free(lbl->reader);
        
        lbl->reader = NULL;
    }

    _laWidget_Destructor((laWidget*)lbl);
}

/*void _jfloLabelWidget_Update(jfloLabelWidget* lbl)
{

}*/

jfloLabelWidget* jfloLabelWidget_New()
{
    jfloLabelWidget* lbl = NULL;

    if(laContext_GetActive() == NULL)
        return NULL;

    lbl = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(jfloLabelWidget));

    _jfloLabelWidget_Constructor(lbl);

    return lbl;
}

laHAlignment jfloLabelWidget_GetHAlignment(jfloLabelWidget* lbl)
{
    if(lbl == NULL)
        return 0;

    return lbl->halign;
}

laResult jfloLabelWidget_SetHAlignment(jfloLabelWidget* lbl,
                                 laHAlignment align)
{
    if(lbl == NULL)
        return LA_FAILURE;
        
    if(lbl->halign == align)
        return LA_SUCCESS;

    invalidateTextRect(lbl);

    lbl->halign = align;

    invalidateTextRect(lbl);
    
    return LA_SUCCESS;
}

laVAlignment jfloLabelWidget_GetVAlignment(jfloLabelWidget* lbl)
{
    if(lbl == NULL)
        return 0;

    return lbl->valign;
}

laResult jfloLabelWidget_SetVAlignment(jfloLabelWidget* lbl,
                                 laVAlignment align)
{
    if(lbl == NULL || lbl->valign == align)
        return LA_FAILURE;

    if(lbl->valign == align)
        return LA_SUCCESS;

    invalidateTextRect(lbl);

    lbl->valign = align;

    invalidateTextRect(lbl);
    
    return LA_SUCCESS;
}

laResult jfloLabelWidget_GetText(jfloLabelWidget* lbl, laString* str)
{
    if(lbl == NULL)
        return LA_FAILURE;
    
    return laString_Copy(str, &lbl->text);
}

laResult jfloLabelWidget_SetText(jfloLabelWidget* lbl, laString str)
{
    if(lbl == NULL)
        return LA_FAILURE;
        
    if(laString_Compare(&lbl->text, &str) == 0)
        return LA_SUCCESS;
        
    invalidateTextRect(lbl);
        
    laString_Copy(&lbl->text, &str);
    
    invalidateTextRect(lbl);
    
    return LA_SUCCESS;
}

#endif // LA_LABEL_WIDGET_ENABLED