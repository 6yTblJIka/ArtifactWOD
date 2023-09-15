////////////////////////////////////////////////////////////////////////////////
//
// ArtifactCore based on TC 6.2.X
// Copyright (C) 2012-2023 TrinityCore
// All Rights Reserved.  Web site TrinityCore https://trinitycore.org/
//
////////////////////////////////////////////////////////////////////////////////

/* ScriptData
SDName: Boss_Baroness_Anastari
SD%Complete: 90
SDComment: MC disabled
SDCategory: Stratholme
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "stratholme.h"

#define SPELL_BANSHEEWAIL   16565
#define SPELL_BANSHEECURSE    16867
#define SPELL_SILENCE    18327
//#define SPELL_POSSESS   17244

class boss_baroness_anastari : public CreatureScript
{
public:
    boss_baroness_anastari() : CreatureScript("boss_baroness_anastari") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_baroness_anastariAI (creature);
    }

    struct boss_baroness_anastariAI : public ScriptedAI
    {
        boss_baroness_anastariAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 BansheeWail_Timer;
        uint32 BansheeCurse_Timer;
        uint32 Silence_Timer;
        //uint32 Possess_Timer;

        void Reset()
        {
            BansheeWail_Timer = 1000;
            BansheeCurse_Timer = 11000;
            Silence_Timer = 13000;
            //Possess_Timer = 35000;
        }

        void EnterCombat(Unit* /*who*/)
        {
        }

         void JustDied(Unit* /*killer*/)
         {
             if (instance)
                 instance->SetData(TYPE_BARONESS, IN_PROGRESS);
         }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            //BansheeWail
            if (BansheeWail_Timer <= diff)
            {
                if (rand()%100 < 95)
                    DoCast(me->getVictim(), SPELL_BANSHEEWAIL);
                //4 seconds until we should cast this again
                BansheeWail_Timer = 4000;
            }
            else
                BansheeWail_Timer -= diff;

            //BansheeCurse
            if (BansheeCurse_Timer <= diff)
            {
                if (rand()%100 < 75)
                    DoCast(me->getVictim(), SPELL_BANSHEECURSE);
                //18 seconds until we should cast this again
                BansheeCurse_Timer = 18000;
            }
            else
                BansheeCurse_Timer -= diff;

            //Silence
            if (Silence_Timer <= diff)
            {
                if (rand()%100 < 80)
                    DoCast(me->getVictim(), SPELL_SILENCE);
                //13 seconds until we should cast this again
                Silence_Timer = 13000;
            }
            else
                Silence_Timer -= diff;

            //Possess
            //if (Possess_Timer <= diff)
            //{
            //    //Cast
            //    if (rand()%100 < 65)
            //    {
            //        Unit* target = NULL;
            //        target = SelectUnit(SELECT_TARGET_RANDOM, 0);
            //        if (target)DoCast(target, SPELL_POSSESS);
            //    }
            //    //50 seconds until we should cast this again
            //    Possess_Timer = 50000;
            //}
            //else
            //    Possess_Timer -= diff;


            DoMeleeAttackIfReady();
        }
    };

};

#ifndef __clang_analyzer__
void AddSC_boss_baroness_anastari()
{
    new boss_baroness_anastari();
}
#endif