/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Auth/Sha1.h"

#ifndef _WARDEN_KEY_GEN_H
#define _WARDEN_KEY_GEN_H

class SHA1Randx
{
public:
    SHA1Randx(uint8* buff, uint32 size)
    {
        uint32 taken = size / 2;

        sh.Initialize();
        sh.UpdateData(buff, taken);
        sh.Finalize();

        memcpy(o1, sh.GetDigest(), 20);

        sh.Initialize();
        sh.UpdateData(buff + taken, size - taken);
        sh.Finalize();

        memcpy(o2, sh.GetDigest(), 20);

        memset(o0, 0x00, 20);

        FillUp();
    }

    void Generate(uint8* buf, uint32 sz)
    {
        for (uint32 i = 0; i < sz; ++i)
        {
            if (taken == 20)
                FillUp();

            buf[i] = o0[taken];
            taken++;
        }
    }

private:
    void FillUp()
    {
        sh.Initialize();
        sh.UpdateData(o1, 20);
        sh.UpdateData(o0, 20);
        sh.UpdateData(o2, 20);
        sh.Finalize();

        memcpy(o0, sh.GetDigest(), 20);

        taken = 0;
    }

    Sha1Hash sh;
    uint32 taken;
    uint8 o0[20], o1[20], o2[20];
};

#endif