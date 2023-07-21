#ifndef TEXTURE_REGISTER_IS_INCLUDED
#define TEXTURE_REGISTER_IS_INCLUDED

const static float TEX_COL_LEN = 1. / 23.;
const static float TEX_ROW_LEN = 1. / 13.;
const static float TEX_X_PIX_CNT = 220.;
const static float TEX_Y_PIX_CNT = 384.;

class TextureRegister
{
public:
    // all data: {xmin ymin xmax ymax}
    // mario
    const float SMALL_MARIO_STAND[4] = {0 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 16 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
    const float SMALL_MARIO_WALK_0[4] = {17 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 33 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
    const float SMALL_MARIO_WALK_1[4] = {34 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 50 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
    const float SMALL_MARIO_WALK_2[4] = {51 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 67 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
    const float SMALL_MARIO_JUMP[4] = {85 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 101 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
    const float SMALL_MARIO_GG[4] = {102 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 118 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
    const float SMALL_MARIO_FLAG[4] = {187 / TEX_X_PIX_CNT, 170 / TEX_Y_PIX_CNT, 203 / TEX_X_PIX_CNT, 186 / TEX_Y_PIX_CNT};

    const float SMALL_LARGE_MARIO[4] = {136 / TEX_X_PIX_CNT, 271 / TEX_Y_PIX_CNT, 152 / TEX_X_PIX_CNT, 303 / TEX_Y_PIX_CNT};

    const float LARGE_MARIO_STAND[4] = {0 / TEX_X_PIX_CNT, 221 / TEX_Y_PIX_CNT, 16 / TEX_X_PIX_CNT, 253 / TEX_Y_PIX_CNT};
    const float LARGE_MARIO_WALK_0[4] = {17 / TEX_X_PIX_CNT, 221 / TEX_Y_PIX_CNT, 33 / TEX_X_PIX_CNT, 253 / TEX_Y_PIX_CNT};
    const float LARGE_MARIO_WALK_1[4] = {34 / TEX_X_PIX_CNT, 221 / TEX_Y_PIX_CNT, 50 / TEX_X_PIX_CNT, 253 / TEX_Y_PIX_CNT};
    const float LARGE_MARIO_WALK_2[4] = {51 / TEX_X_PIX_CNT, 221 / TEX_Y_PIX_CNT, 67 / TEX_X_PIX_CNT, 253 / TEX_Y_PIX_CNT};
    const float LARGE_MARIO_JUMP[4] = {85 / TEX_X_PIX_CNT, 221 / TEX_Y_PIX_CNT, 101 / TEX_X_PIX_CNT, 253 / TEX_Y_PIX_CNT};
    const float LARGE_MARIO_GG[4] = {102 / TEX_X_PIX_CNT, 221 / TEX_Y_PIX_CNT, 118 / TEX_X_PIX_CNT, 253 / TEX_Y_PIX_CNT};
    const float LARGE_MARIO_FLAG[4] = {17 / TEX_X_PIX_CNT, 271 / TEX_Y_PIX_CNT, 33 / TEX_X_PIX_CNT, 287 / TEX_Y_PIX_CNT};

    // breakable block
    const float BREAKABLE_BLOCK[4] = {85 / TEX_X_PIX_CNT, 0 / TEX_Y_PIX_CNT, 101 / TEX_X_PIX_CNT, 16 / TEX_Y_PIX_CNT};

    // question block
    const float QUESTION_BLOCK_Q_0[4] = {0 / TEX_X_PIX_CNT, 204 / TEX_Y_PIX_CNT, 16 / TEX_X_PIX_CNT, 220 / TEX_Y_PIX_CNT};
    const float QUESTION_BLOCK_Q_1[4] = {17 / TEX_X_PIX_CNT, 204 / TEX_Y_PIX_CNT, 33 / TEX_X_PIX_CNT, 220 / TEX_Y_PIX_CNT};
    const float QUESTION_BLOCK_Q_2[4] = {34 / TEX_X_PIX_CNT, 204 / TEX_Y_PIX_CNT, 50 / TEX_X_PIX_CNT, 220 / TEX_Y_PIX_CNT};
    const float QUESTION_BLOCK_SOLID[4] = {51 / TEX_X_PIX_CNT, 204 / TEX_Y_PIX_CNT, 67 / TEX_X_PIX_CNT, 220 / TEX_Y_PIX_CNT};

    // coin
    const float COIN_0[4] = {153 / TEX_X_PIX_CNT, 153 / TEX_Y_PIX_CNT, 169 / TEX_X_PIX_CNT, 169 / TEX_Y_PIX_CNT};
    const float COIN_1[4] = {170 / TEX_X_PIX_CNT, 153 / TEX_Y_PIX_CNT, 186 / TEX_X_PIX_CNT, 169 / TEX_Y_PIX_CNT};
    const float COIN_2[4] = {187 / TEX_X_PIX_CNT, 153 / TEX_Y_PIX_CNT, 203 / TEX_X_PIX_CNT, 169 / TEX_Y_PIX_CNT};
    const float COIN_3[4] = {204 / TEX_X_PIX_CNT, 153 / TEX_Y_PIX_CNT, 220 / TEX_X_PIX_CNT, 169 / TEX_Y_PIX_CNT};

    // goomba
    const float GOOMBA_NORMAL[4] = {119 / TEX_X_PIX_CNT, 187 / TEX_Y_PIX_CNT, 135 / TEX_X_PIX_CNT, 203 / TEX_Y_PIX_CNT};
    const float GOOMBA_DIE[4] = {102 / TEX_X_PIX_CNT, 187 / TEX_Y_PIX_CNT, 118 / TEX_X_PIX_CNT, 203 / TEX_Y_PIX_CNT};

    // mushroom
    const float RED_MUSHROOM[4] = {119 / TEX_X_PIX_CNT, 204 / TEX_Y_PIX_CNT, 135 / TEX_X_PIX_CNT, 220 / TEX_Y_PIX_CNT};
    const float GREEN_MUSHROOM[4] = {136 / TEX_X_PIX_CNT, 204 / TEX_Y_PIX_CNT, 152 / TEX_X_PIX_CNT, 220 / TEX_Y_PIX_CNT};

    // immortal star
    const float STAR_0[4] = {153 / TEX_X_PIX_CNT, 295 / TEX_Y_PIX_CNT, 169 / TEX_X_PIX_CNT, 311 / TEX_Y_PIX_CNT};
    const float STAR_1[4] = {169 / TEX_X_PIX_CNT, 295 / TEX_Y_PIX_CNT, 185 / TEX_X_PIX_CNT, 311 / TEX_Y_PIX_CNT};
    const float STAR_2[4] = {185 / TEX_X_PIX_CNT, 295 / TEX_Y_PIX_CNT, 201 / TEX_X_PIX_CNT, 311 / TEX_Y_PIX_CNT};
    const float STAR_3[4] = {201 / TEX_X_PIX_CNT, 295 / TEX_Y_PIX_CNT, 217 / TEX_X_PIX_CNT, 311 / TEX_Y_PIX_CNT};

    // fire flower
    const float FIRE_FLOWER_0[4] = {136 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 152 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
    const float FIRE_FLOWER_1[4] = {153 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 169 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
    const float FIRE_FLOWER_2[4] = {170 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 186 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
    const float FIRE_FLOWER_3[4] = {187 / TEX_X_PIX_CNT, 254 / TEX_Y_PIX_CNT, 203 / TEX_X_PIX_CNT, 270 / TEX_Y_PIX_CNT};
};

#endif