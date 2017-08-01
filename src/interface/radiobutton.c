/**********************************************************************
 *
 * TileLess
 *
 * TileLess is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * TileLess is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TileLess.  If not, see <http://www.gnu.org/licenses/>.
 *
 **********************************************************************
 *
 * Copyright (C) 2016-2017 Nicklas Avén
 *
 **********************************************************************/


#include "../theclient.h"
#include "../mem.h"
#include "interface.h"






static int radio_clicked(void *ctrl, void *val, tileless_event_func_in_func func_in_func)
{
    int i, v;
    struct CTRL *t = (struct CTRL *) ctrl;
    TEXTBLOCK *txt;
    struct CTRL *radio_master = t->spatial_family->parent;
    v = 0;
    for (i=0; i<radio_master->spatial_family->n_children; i++)
    {
        struct CTRL *rb = radio_master->spatial_family->children[i];
        func_in_func((void*) rb,(void*) &v);
        // ((LAYER_RUNTIME*) rb->obj)->info_active = 0;
        if(rb->txt)
        {
            destroy_textblock(rb->txt);
            rb->txt = 0;
        }
    }


    /*
    txt = init_txt(5);
    add_txt(txt, "O");*/
    txt = init_textblock(1);
    append_2_textblock(txt,"O", fonts[0]->fss->fs[2].bold);
    t->txt=txt;
    v = 1;
    func_in_func((void*) t, &v);
    // ((LAYER_RUNTIME*) t->obj)->info_active = 1;


    return 0;
}





struct CTRL* init_radio(struct CTRL *spatial_parent,struct CTRL *logical_parent, GLshort *box,GLfloat *color,TEXTBLOCK *txt, GLfloat *txt_margin,int default_active, int z)
{


    return register_control(RADIOMASTER, spatial_parent, logical_parent,NULL, NULL, NULL,box, color, txt, txt_margin, default_active, z);


}






struct CTRL* add_radio_button(struct CTRL *radio_master, tileless_event_func_in_func set_unset, GLshort size, GLshort row_dist, int default_active, int set)
{

    int i;
    GLshort box[4];
    GLshort origo_y;
    GLshort master_width = radio_master->box[2] - radio_master->box[0];
    box[0] = radio_master->box[0] + master_width/2 - size/2;
    struct CTRL *radio_button;
    if(radio_master->spatial_family->n_children)
    {
        box[3] = radio_master->spatial_family->children[radio_master->spatial_family->n_children -1]->box[1] - row_dist; //we get miny from the last radiobutton from before
    }
    else
    {

        box[3] = radio_master->box[3] - row_dist; //so far we only support vertical radiobuttons so all share x-values

    }

    box[1] = box[3] - size;
    box[2] = box[0] + size;


    GLfloat color[4];

    /*GLfloat *master_color = radio_master->color;

    for (i = 0;i<3;i++)
    {
        color[i] = master_color[i] - 50;
        if (color[i] < 0)
            color[i] += 255;
    }*/
    color[3] = 255;

    color[0] = 255;
    color[1] = 255;
    color[2] = 255;

    GLfloat text_margins[] = {3,3};
    if(set)
    {
        
        TEXTBLOCK *txt;
        /*
        txt = init_txt(5);
        add_txt(txt, "O");*/
        txt = init_textblock(1);
        append_2_textblock(txt,"O", fonts[0]->fss->fs[2].bold);
    
        radio_button = register_control(RADIOBUTTON, radio_master, radio_master,radio_clicked,NULL, set_unset, box, color, txt, text_margins, default_active,radio_master->z + 1);
    }
    else
        radio_button = register_control(RADIOBUTTON, radio_master, radio_master,radio_clicked,NULL, set_unset, box, color, NULL,text_margins, default_active,radio_master->z + 1);

    return radio_button;
}








