/*! @file level_system.c
 *
 *
 *
 *
 *
 */

/************************************************************************
* INCLUDES
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"
#include "conversions.h"
#include "entity_system.h"
#include "player_system.h"
#include "level_system.h"

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

void LVLSYS_LoadLevel(void)
{
    FILE* lvl_file = fopen("level_one.txt", "r");

    if (NULL == lvl_file)
    {
        LOGG_err("Error when opening Level File");
        return;
    }

    char file_line[100];
    bool is_first_line = true;

    while (false == feof(lvl_file))
    {
        if (NULL != fgets(file_line, 100, lvl_file))
        {
            // Remove the New Line char at the end of each line
            size_t line_len = strlen(file_line);
            if (file_line[line_len-1] == '\n')
            {
                file_line[line_len-1] = '\0';
            }

            if (true == is_first_line)
            {
                LOGG_info("Header Line: %s", file_line);
                is_first_line = false;
                continue;
            }

            char* tokens[32];
            uint8_t token_index = 0;
            char* token = strtok(file_line, ",");
            while (NULL != token)
            {
                tokens[token_index] = token;
                token = strtok(NULL, ",");
                token_index++;
            }

            // XCoord,YCoord,Width,Height,Colour,Type,Extras
            double         x_coord       = 0;
            double         y_coord       = 0;
            double         width         = 0;
            double         height        = 0;
            REND_colour    colour        = {0};
            char           type[32];
            uint8_t        player_number = 0;
            PLAYER_key_map key_map       = {0};

            x_coord = atof(tokens[0]);
            y_coord = atof(tokens[1]);
            width   = atof(tokens[2]);
            height  = atof(tokens[3]);
            colour  = CONV_HexToColour(tokens[4]);
            strncpy(type, tokens[5], strlen(tokens[5])+1);

            LOGG_info("Entity Data: X Coord = %f; Y Coord = %f; Width = %f; Height = %f; Colour = %f:%f:%f; Type = %s",
                        x_coord, y_coord, width, height, colour.red, colour.green, colour.blue, type);

            if (0 == strcmp(type, "FLOOR"))
            {
                const ENTITY_entity* floor = ENTITY_CreateStaticEntity(x_coord, y_coord, width, height, colour);
                LOGG_info("Floor Entity ID = %d", floor->id);
            }
            else if (0 == strcmp(type, "PLAYER"))
            {
                player_number = atoi(tokens[6]);

                if (0 == strcmp(tokens[7], "WASD"))
                {
                    key_map = KEY_MAP_WASD;
                }

                ENTITY_entity* player = ENTITY_CreatePlayerEntity(x_coord, y_coord, width, height, colour, player_number, key_map);
                LOGG_info("Player Entity ID = %d", player->id);
            }
            else if (0 == strcmp(type, "PLATFORM"))
            {
                const ENTITY_entity* static_entity = ENTITY_CreateStaticEntity(x_coord, y_coord, width, height, colour);
                LOGG_info("Static Entity ID = %d", static_entity->id);
            }
        }
    }

    fclose(lvl_file);
}
