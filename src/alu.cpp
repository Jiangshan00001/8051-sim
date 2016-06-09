#include <iostream>
#include <string>
#include "flash.hpp"
#include "alu.hpp"
#include "instruction_set.hpp"
#include "exceptions.hpp"
#include "sfr.hpp"

class SfrSp: public Sfr
{
  public:
    SfrSp(Alu &alu);
    void OnWrite(std::uint8_t data);
    std::uint8_t Read();
  private:
    Alu &alu;
};

class SfrDpl: public Sfr
{
  public:
    SfrDpl(Alu &alu);
    void OnWrite(std::uint8_t data);
    std::uint8_t Read();
  private:
    Alu &alu;
};

class SfrIP: public Sfr
{
  public:
    SfrIP(Alu &alu);
    void OnWrite(std::uint8_t data);
    std::uint8_t Read();
  private:
    Alu &alu;
};

class SfrSFRPAGE: public Sfr
{
  public:
    SfrSFRPAGE(Alu &alu);
    void OnWrite(std::uint8_t data);
    std::uint8_t Read();
  private:
    Alu &alu;
};

Alu::Alu(Flash &f, Memory &x, std::uint16_t iramSize): flash(f), xram(x)
{
  iram = new std::uint8_t[iramSize];
  INC_7 *inc_7 = new INC_7(*this);
  instructionSet[inc_7->GetOpcode()] = inc_7;
  ACALL_11 *acall_11 = new ACALL_11(*this);
  instructionSet[acall_11->GetOpcode()] = acall_11;
  ACALL_31 *acall_31 = new ACALL_31(*this);
  instructionSet[acall_31->GetOpcode()] = acall_31;
  ACALL_51 *acall_51 = new ACALL_51(*this);
  instructionSet[acall_51->GetOpcode()] = acall_51;
  ACALL_71 *acall_71 = new ACALL_71(*this);
  instructionSet[acall_71->GetOpcode()] = acall_71;
  ACALL_91 *acall_91 = new ACALL_91(*this);
  instructionSet[acall_91->GetOpcode()] = acall_91;
  ACALL_B1 *acall_b1 = new ACALL_B1(*this);
  instructionSet[acall_b1->GetOpcode()] = acall_b1;
  ACALL_D1 *acall_d1 = new ACALL_D1(*this);
  instructionSet[acall_d1->GetOpcode()] = acall_d1;
  ACALL_F1 *acall_f1 = new ACALL_F1(*this);
  instructionSet[acall_f1->GetOpcode()] = acall_f1;
  ADD_24 *add_24 = new ADD_24(*this);
  instructionSet[add_24->GetOpcode()] = add_24;
  ADD_25 *add_25 = new ADD_25(*this);
  instructionSet[add_25->GetOpcode()] = add_25;
  ADD_26 *add_26 = new ADD_26(*this);
  instructionSet[add_26->GetOpcode()] = add_26;
  ADD_27 *add_27 = new ADD_27(*this);
  instructionSet[add_27->GetOpcode()] = add_27;
  ADD_28 *add_28 = new ADD_28(*this);
  instructionSet[add_28->GetOpcode()] = add_28;
  ADD_29 *add_29 = new ADD_29(*this);
  instructionSet[add_29->GetOpcode()] = add_29;
  ADD_2A *add_2a = new ADD_2A(*this);
  instructionSet[add_2a->GetOpcode()] = add_2a;
  ADD_2B *add_2b = new ADD_2B(*this);
  instructionSet[add_2b->GetOpcode()] = add_2b;
  ADD_2C *add_2c = new ADD_2C(*this);
  instructionSet[add_2c->GetOpcode()] = add_2c;
  ADD_2D *add_2d = new ADD_2D(*this);
  instructionSet[add_2d->GetOpcode()] = add_2d;
  ADD_2E *add_2e = new ADD_2E(*this);
  instructionSet[add_2e->GetOpcode()] = add_2e;
  ADD_2F *add_2f = new ADD_2F(*this);
  instructionSet[add_2f->GetOpcode()] = add_2f;
  ADDC_34 *addc_34 = new ADDC_34(*this);
  instructionSet[addc_34->GetOpcode()] = addc_34;
  ADDC_35 *addc_35 = new ADDC_35(*this);
  instructionSet[addc_35->GetOpcode()] = addc_35;
  ADDC_36 *addc_36 = new ADDC_36(*this);
  instructionSet[addc_36->GetOpcode()] = addc_36;
  ADDC_37 *addc_37 = new ADDC_37(*this);
  instructionSet[addc_37->GetOpcode()] = addc_37;
  ADDC_38 *addc_38 = new ADDC_38(*this);
  instructionSet[addc_38->GetOpcode()] = addc_38;
  ADDC_39 *addc_39 = new ADDC_39(*this);
  instructionSet[addc_39->GetOpcode()] = addc_39;
  ADDC_3A *addc_3a = new ADDC_3A(*this);
  instructionSet[addc_3a->GetOpcode()] = addc_3a;
  ADDC_3B *addc_3b = new ADDC_3B(*this);
  instructionSet[addc_3b->GetOpcode()] = addc_3b;
  ADDC_3C *addc_3c = new ADDC_3C(*this);
  instructionSet[addc_3c->GetOpcode()] = addc_3c;
  ADDC_3D *addc_3d = new ADDC_3D(*this);
  instructionSet[addc_3d->GetOpcode()] = addc_3d;
  ADDC_3E *addc_3e = new ADDC_3E(*this);
  instructionSet[addc_3e->GetOpcode()] = addc_3e;
  ADDC_3F *addc_3f = new ADDC_3F(*this);
  instructionSet[addc_3f->GetOpcode()] = addc_3f;
  AJMP_1 *ajmp_1 = new AJMP_1(*this);
  instructionSet[ajmp_1->GetOpcode()] = ajmp_1;
  AJMP_21 *ajmp_21 = new AJMP_21(*this);
  instructionSet[ajmp_21->GetOpcode()] = ajmp_21;
  AJMP_41 *ajmp_41 = new AJMP_41(*this);
  instructionSet[ajmp_41->GetOpcode()] = ajmp_41;
  AJMP_61 *ajmp_61 = new AJMP_61(*this);
  instructionSet[ajmp_61->GetOpcode()] = ajmp_61;
  AJMP_81 *ajmp_81 = new AJMP_81(*this);
  instructionSet[ajmp_81->GetOpcode()] = ajmp_81;
  AJMP_A1 *ajmp_a1 = new AJMP_A1(*this);
  instructionSet[ajmp_a1->GetOpcode()] = ajmp_a1;
  AJMP_C1 *ajmp_c1 = new AJMP_C1(*this);
  instructionSet[ajmp_c1->GetOpcode()] = ajmp_c1;
  AJMP_E1 *ajmp_e1 = new AJMP_E1(*this);
  instructionSet[ajmp_e1->GetOpcode()] = ajmp_e1;
  ANL_52 *anl_52 = new ANL_52(*this);
  instructionSet[anl_52->GetOpcode()] = anl_52;
  ANL_53 *anl_53 = new ANL_53(*this);
  instructionSet[anl_53->GetOpcode()] = anl_53;
  ANL_54 *anl_54 = new ANL_54(*this);
  instructionSet[anl_54->GetOpcode()] = anl_54;
  ANL_55 *anl_55 = new ANL_55(*this);
  instructionSet[anl_55->GetOpcode()] = anl_55;
  ANL_56 *anl_56 = new ANL_56(*this);
  instructionSet[anl_56->GetOpcode()] = anl_56;
  ANL_57 *anl_57 = new ANL_57(*this);
  instructionSet[anl_57->GetOpcode()] = anl_57;
  ANL_58 *anl_58 = new ANL_58(*this);
  instructionSet[anl_58->GetOpcode()] = anl_58;
  ANL_59 *anl_59 = new ANL_59(*this);
  instructionSet[anl_59->GetOpcode()] = anl_59;
  ANL_5A *anl_5a = new ANL_5A(*this);
  instructionSet[anl_5a->GetOpcode()] = anl_5a;
  ANL_5B *anl_5b = new ANL_5B(*this);
  instructionSet[anl_5b->GetOpcode()] = anl_5b;
  ANL_5C *anl_5c = new ANL_5C(*this);
  instructionSet[anl_5c->GetOpcode()] = anl_5c;
  ANL_5D *anl_5d = new ANL_5D(*this);
  instructionSet[anl_5d->GetOpcode()] = anl_5d;
  ANL_5E *anl_5e = new ANL_5E(*this);
  instructionSet[anl_5e->GetOpcode()] = anl_5e;
  ANL_5F *anl_5f = new ANL_5F(*this);
  instructionSet[anl_5f->GetOpcode()] = anl_5f;
  ANL_82 *anl_82 = new ANL_82(*this);
  instructionSet[anl_82->GetOpcode()] = anl_82;
  ANL_B0 *anl_b0 = new ANL_B0(*this);
  instructionSet[anl_b0->GetOpcode()] = anl_b0;
  CJNE_B4 *cjne_b4 = new CJNE_B4(*this);
  instructionSet[cjne_b4->GetOpcode()] = cjne_b4;
  CJNE_B5 *cjne_b5 = new CJNE_B5(*this);
  instructionSet[cjne_b5->GetOpcode()] = cjne_b5;
  CJNE_B6 *cjne_b6 = new CJNE_B6(*this);
  instructionSet[cjne_b6->GetOpcode()] = cjne_b6;
  CJNE_B7 *cjne_b7 = new CJNE_B7(*this);
  instructionSet[cjne_b7->GetOpcode()] = cjne_b7;
  CJNE_B8 *cjne_b8 = new CJNE_B8(*this);
  instructionSet[cjne_b8->GetOpcode()] = cjne_b8;
  CJNE_B9 *cjne_b9 = new CJNE_B9(*this);
  instructionSet[cjne_b9->GetOpcode()] = cjne_b9;
  CJNE_BA *cjne_ba = new CJNE_BA(*this);
  instructionSet[cjne_ba->GetOpcode()] = cjne_ba;
  CJNE_BB *cjne_bb = new CJNE_BB(*this);
  instructionSet[cjne_bb->GetOpcode()] = cjne_bb;
  CJNE_BC *cjne_bc = new CJNE_BC(*this);
  instructionSet[cjne_bc->GetOpcode()] = cjne_bc;
  CJNE_BD *cjne_bd = new CJNE_BD(*this);
  instructionSet[cjne_bd->GetOpcode()] = cjne_bd;
  CJNE_BE *cjne_be = new CJNE_BE(*this);
  instructionSet[cjne_be->GetOpcode()] = cjne_be;
  CJNE_BF *cjne_bf = new CJNE_BF(*this);
  instructionSet[cjne_bf->GetOpcode()] = cjne_bf;
  CLR_C2 *clr_c2 = new CLR_C2(*this);
  instructionSet[clr_c2->GetOpcode()] = clr_c2;
  CLR_C3 *clr_c3 = new CLR_C3(*this);
  instructionSet[clr_c3->GetOpcode()] = clr_c3;
  CLR_E4 *clr_e4 = new CLR_E4(*this);
  instructionSet[clr_e4->GetOpcode()] = clr_e4;
  CPL_F4 *cpl_f4 = new CPL_F4(*this);
  instructionSet[cpl_f4->GetOpcode()] = cpl_f4;
  CPL_B3 *cpl_b3 = new CPL_B3(*this);
  instructionSet[cpl_b3->GetOpcode()] = cpl_b3;
  CPL_B2 *cpl_b2 = new CPL_B2(*this);
  instructionSet[cpl_b2->GetOpcode()] = cpl_b2;
  DA_D4 *da_d4 = new DA_D4(*this);
  instructionSet[da_d4->GetOpcode()] = da_d4;
  DEC_15 *dec_15 = new DEC_15(*this);
  instructionSet[dec_15->GetOpcode()] = dec_15;
  DEC_14 *dec_14 = new DEC_14(*this);
  instructionSet[dec_14->GetOpcode()] = dec_14;
  DEC_16 *dec_16 = new DEC_16(*this);
  instructionSet[dec_16->GetOpcode()] = dec_16;
  DEC_17 *dec_17 = new DEC_17(*this);
  instructionSet[dec_17->GetOpcode()] = dec_17;
  DEC_18 *dec_18 = new DEC_18(*this);
  instructionSet[dec_18->GetOpcode()] = dec_18;
  DEC_19 *dec_19 = new DEC_19(*this);
  instructionSet[dec_19->GetOpcode()] = dec_19;
  DEC_1A *dec_1a = new DEC_1A(*this);
  instructionSet[dec_1a->GetOpcode()] = dec_1a;
  DEC_1B *dec_1b = new DEC_1B(*this);
  instructionSet[dec_1b->GetOpcode()] = dec_1b;
  DEC_1C *dec_1c = new DEC_1C(*this);
  instructionSet[dec_1c->GetOpcode()] = dec_1c;
  DEC_1D *dec_1d = new DEC_1D(*this);
  instructionSet[dec_1d->GetOpcode()] = dec_1d;
  DEC_1E *dec_1e = new DEC_1E(*this);
  instructionSet[dec_1e->GetOpcode()] = dec_1e;
  DEC_1F *dec_1f = new DEC_1F(*this);
  instructionSet[dec_1f->GetOpcode()] = dec_1f;
  DIV_84 *div_84 = new DIV_84(*this);
  instructionSet[div_84->GetOpcode()] = div_84;
  DJNZ_D5 *djnz_d5 = new DJNZ_D5(*this);
  instructionSet[djnz_d5->GetOpcode()] = djnz_d5;
  DJNZ_D8 *djnz_d8 = new DJNZ_D8(*this);
  instructionSet[djnz_d8->GetOpcode()] = djnz_d8;
  DJNZ_D9 *djnz_d9 = new DJNZ_D9(*this);
  instructionSet[djnz_d9->GetOpcode()] = djnz_d9;
  DJNZ_DA *djnz_da = new DJNZ_DA(*this);
  instructionSet[djnz_da->GetOpcode()] = djnz_da;
  DJNZ_DB *djnz_db = new DJNZ_DB(*this);
  instructionSet[djnz_db->GetOpcode()] = djnz_db;
  DJNZ_DC *djnz_dc = new DJNZ_DC(*this);
  instructionSet[djnz_dc->GetOpcode()] = djnz_dc;
  DJNZ_DD *djnz_dd = new DJNZ_DD(*this);
  instructionSet[djnz_dd->GetOpcode()] = djnz_dd;
  DJNZ_DE *djnz_de = new DJNZ_DE(*this);
  instructionSet[djnz_de->GetOpcode()] = djnz_de;
  DJNZ_DF *djnz_df = new DJNZ_DF(*this);
  instructionSet[djnz_df->GetOpcode()] = djnz_df;
  INC_5 *inc_5 = new INC_5(*this);
  instructionSet[inc_5->GetOpcode()] = inc_5;
  INC_4 *inc_4 = new INC_4(*this);
  instructionSet[inc_4->GetOpcode()] = inc_4;
  INC_6 *inc_6 = new INC_6(*this);
  instructionSet[inc_6->GetOpcode()] = inc_6;
  INC_8 *inc_8 = new INC_8(*this);
  instructionSet[inc_8->GetOpcode()] = inc_8;
  INC_9 *inc_9 = new INC_9(*this);
  instructionSet[inc_9->GetOpcode()] = inc_9;
  INC_A *inc_a = new INC_A(*this);
  instructionSet[inc_a->GetOpcode()] = inc_a;
  INC_B *inc_b = new INC_B(*this);
  instructionSet[inc_b->GetOpcode()] = inc_b;
  INC_C *inc_c = new INC_C(*this);
  instructionSet[inc_c->GetOpcode()] = inc_c;
  INC_D *inc_d = new INC_D(*this);
  instructionSet[inc_d->GetOpcode()] = inc_d;
  INC_E *inc_e = new INC_E(*this);
  instructionSet[inc_e->GetOpcode()] = inc_e;
  INC_F *inc_f = new INC_F(*this);
  instructionSet[inc_f->GetOpcode()] = inc_f;
  INC_A3 *inc_a3 = new INC_A3(*this);
  instructionSet[inc_a3->GetOpcode()] = inc_a3;
  JB_20 *jb_20 = new JB_20(*this);
  instructionSet[jb_20->GetOpcode()] = jb_20;
  JBC_10 *jbc_10 = new JBC_10(*this);
  instructionSet[jbc_10->GetOpcode()] = jbc_10;
  JC_40 *jc_40 = new JC_40(*this);
  instructionSet[jc_40->GetOpcode()] = jc_40;
  JMP_73 *jmp_73 = new JMP_73(*this);
  instructionSet[jmp_73->GetOpcode()] = jmp_73;
  JNB_30 *jnb_30 = new JNB_30(*this);
  instructionSet[jnb_30->GetOpcode()] = jnb_30;
  JNC_50 *jnc_50 = new JNC_50(*this);
  instructionSet[jnc_50->GetOpcode()] = jnc_50;
  JNZ_70 *jnz_70 = new JNZ_70(*this);
  instructionSet[jnz_70->GetOpcode()] = jnz_70;
  JZ_60 *jz_60 = new JZ_60(*this);
  instructionSet[jz_60->GetOpcode()] = jz_60;
  LCALL_12 *lcall_12 = new LCALL_12(*this);
  instructionSet[lcall_12->GetOpcode()] = lcall_12;
  LJMP_2 *ljmp_2 = new LJMP_2(*this);
  instructionSet[ljmp_2->GetOpcode()] = ljmp_2;
  MOV_90 *mov_90 = new MOV_90(*this);
  instructionSet[mov_90->GetOpcode()] = mov_90;
  MOV_75 *mov_75 = new MOV_75(*this);
  instructionSet[mov_75->GetOpcode()] = mov_75;
  MOV_85 *mov_85 = new MOV_85(*this);
  instructionSet[mov_85->GetOpcode()] = mov_85;
  MOV_76 *mov_76 = new MOV_76(*this);
  instructionSet[mov_76->GetOpcode()] = mov_76;
  MOV_77 *mov_77 = new MOV_77(*this);
  instructionSet[mov_77->GetOpcode()] = mov_77;
  MOV_A6 *mov_a6 = new MOV_A6(*this);
  instructionSet[mov_a6->GetOpcode()] = mov_a6;
  MOV_A7 *mov_a7 = new MOV_A7(*this);
  instructionSet[mov_a7->GetOpcode()] = mov_a7;
  MOV_74 *mov_74 = new MOV_74(*this);
  instructionSet[mov_74->GetOpcode()] = mov_74;
  MOV_E5 *mov_e5 = new MOV_E5(*this);
  instructionSet[mov_e5->GetOpcode()] = mov_e5;
  MOV_A2 *mov_a2 = new MOV_A2(*this);
  instructionSet[mov_a2->GetOpcode()] = mov_a2;
  MOV_78 *mov_78 = new MOV_78(*this);
  instructionSet[mov_78->GetOpcode()] = mov_78;
  MOV_79 *mov_79 = new MOV_79(*this);
  instructionSet[mov_79->GetOpcode()] = mov_79;
  MOV_7A *mov_7a = new MOV_7A(*this);
  instructionSet[mov_7a->GetOpcode()] = mov_7a;
  MOV_7B *mov_7b = new MOV_7B(*this);
  instructionSet[mov_7b->GetOpcode()] = mov_7b;
  MOV_7C *mov_7c = new MOV_7C(*this);
  instructionSet[mov_7c->GetOpcode()] = mov_7c;
  MOV_7D *mov_7d = new MOV_7D(*this);
  instructionSet[mov_7d->GetOpcode()] = mov_7d;
  MOV_7E *mov_7e = new MOV_7E(*this);
  instructionSet[mov_7e->GetOpcode()] = mov_7e;
  MOV_7F *mov_7f = new MOV_7F(*this);
  instructionSet[mov_7f->GetOpcode()] = mov_7f;
  MOV_A8 *mov_a8 = new MOV_A8(*this);
  instructionSet[mov_a8->GetOpcode()] = mov_a8;
  MOV_A9 *mov_a9 = new MOV_A9(*this);
  instructionSet[mov_a9->GetOpcode()] = mov_a9;
  MOV_AA *mov_aa = new MOV_AA(*this);
  instructionSet[mov_aa->GetOpcode()] = mov_aa;
  MOV_AB *mov_ab = new MOV_AB(*this);
  instructionSet[mov_ab->GetOpcode()] = mov_ab;
  MOV_AC *mov_ac = new MOV_AC(*this);
  instructionSet[mov_ac->GetOpcode()] = mov_ac;
  MOV_AD *mov_ad = new MOV_AD(*this);
  instructionSet[mov_ad->GetOpcode()] = mov_ad;
  MOV_AE *mov_ae = new MOV_AE(*this);
  instructionSet[mov_ae->GetOpcode()] = mov_ae;
  MOV_AF *mov_af = new MOV_AF(*this);
  instructionSet[mov_af->GetOpcode()] = mov_af;
  MOV_92 *mov_92 = new MOV_92(*this);
  instructionSet[mov_92->GetOpcode()] = mov_92;
  MOV_86 *mov_86 = new MOV_86(*this);
  instructionSet[mov_86->GetOpcode()] = mov_86;
  MOV_87 *mov_87 = new MOV_87(*this);
  instructionSet[mov_87->GetOpcode()] = mov_87;
  MOV_88 *mov_88 = new MOV_88(*this);
  instructionSet[mov_88->GetOpcode()] = mov_88;
  MOV_89 *mov_89 = new MOV_89(*this);
  instructionSet[mov_89->GetOpcode()] = mov_89;
  MOV_8A *mov_8a = new MOV_8A(*this);
  instructionSet[mov_8a->GetOpcode()] = mov_8a;
  MOV_8B *mov_8b = new MOV_8B(*this);
  instructionSet[mov_8b->GetOpcode()] = mov_8b;
  MOV_8C *mov_8c = new MOV_8C(*this);
  instructionSet[mov_8c->GetOpcode()] = mov_8c;
  MOV_8D *mov_8d = new MOV_8D(*this);
  instructionSet[mov_8d->GetOpcode()] = mov_8d;
  MOV_8E *mov_8e = new MOV_8E(*this);
  instructionSet[mov_8e->GetOpcode()] = mov_8e;
  MOV_8F *mov_8f = new MOV_8F(*this);
  instructionSet[mov_8f->GetOpcode()] = mov_8f;
  MOV_F5 *mov_f5 = new MOV_F5(*this);
  instructionSet[mov_f5->GetOpcode()] = mov_f5;
  MOV_F6 *mov_f6 = new MOV_F6(*this);
  instructionSet[mov_f6->GetOpcode()] = mov_f6;
  MOV_F7 *mov_f7 = new MOV_F7(*this);
  instructionSet[mov_f7->GetOpcode()] = mov_f7;
  MOV_E6 *mov_e6 = new MOV_E6(*this);
  instructionSet[mov_e6->GetOpcode()] = mov_e6;
  MOV_E7 *mov_e7 = new MOV_E7(*this);
  instructionSet[mov_e7->GetOpcode()] = mov_e7;
  MOV_E8 *mov_e8 = new MOV_E8(*this);
  instructionSet[mov_e8->GetOpcode()] = mov_e8;
  MOV_E9 *mov_e9 = new MOV_E9(*this);
  instructionSet[mov_e9->GetOpcode()] = mov_e9;
  MOV_EA *mov_ea = new MOV_EA(*this);
  instructionSet[mov_ea->GetOpcode()] = mov_ea;
  MOV_EB *mov_eb = new MOV_EB(*this);
  instructionSet[mov_eb->GetOpcode()] = mov_eb;
  MOV_EC *mov_ec = new MOV_EC(*this);
  instructionSet[mov_ec->GetOpcode()] = mov_ec;
  MOV_ED *mov_ed = new MOV_ED(*this);
  instructionSet[mov_ed->GetOpcode()] = mov_ed;
  MOV_EE *mov_ee = new MOV_EE(*this);
  instructionSet[mov_ee->GetOpcode()] = mov_ee;
  MOV_EF *mov_ef = new MOV_EF(*this);
  instructionSet[mov_ef->GetOpcode()] = mov_ef;
  MOV_F8 *mov_f8 = new MOV_F8(*this);
  instructionSet[mov_f8->GetOpcode()] = mov_f8;
  MOV_F9 *mov_f9 = new MOV_F9(*this);
  instructionSet[mov_f9->GetOpcode()] = mov_f9;
  MOV_FA *mov_fa = new MOV_FA(*this);
  instructionSet[mov_fa->GetOpcode()] = mov_fa;
  MOV_FB *mov_fb = new MOV_FB(*this);
  instructionSet[mov_fb->GetOpcode()] = mov_fb;
  MOV_FC *mov_fc = new MOV_FC(*this);
  instructionSet[mov_fc->GetOpcode()] = mov_fc;
  MOV_FD *mov_fd = new MOV_FD(*this);
  instructionSet[mov_fd->GetOpcode()] = mov_fd;
  MOV_FE *mov_fe = new MOV_FE(*this);
  instructionSet[mov_fe->GetOpcode()] = mov_fe;
  MOV_FF *mov_ff = new MOV_FF(*this);
  instructionSet[mov_ff->GetOpcode()] = mov_ff;
  MOVC_93 *movc_93 = new MOVC_93(*this);
  instructionSet[movc_93->GetOpcode()] = movc_93;
  MOVC_83 *movc_83 = new MOVC_83(*this);
  instructionSet[movc_83->GetOpcode()] = movc_83;
  MOVX_F0 *movx_f0 = new MOVX_F0(*this);
  instructionSet[movx_f0->GetOpcode()] = movx_f0;
  MOVX_F2 *movx_f2 = new MOVX_F2(*this);
  instructionSet[movx_f2->GetOpcode()] = movx_f2;
  MOVX_F3 *movx_f3 = new MOVX_F3(*this);
  instructionSet[movx_f3->GetOpcode()] = movx_f3;
  MOVX_E0 *movx_e0 = new MOVX_E0(*this);
  instructionSet[movx_e0->GetOpcode()] = movx_e0;
  MOVX_E2 *movx_e2 = new MOVX_E2(*this);
  instructionSet[movx_e2->GetOpcode()] = movx_e2;
  MOVX_E3 *movx_e3 = new MOVX_E3(*this);
  instructionSet[movx_e3->GetOpcode()] = movx_e3;
  MUL_A4 *mul_a4 = new MUL_A4(*this);
  instructionSet[mul_a4->GetOpcode()] = mul_a4;
  NOP *nop = new NOP(*this);
  instructionSet[nop->GetOpcode()] = nop;
  ORL_43 *orl_43 = new ORL_43(*this);
  instructionSet[orl_43->GetOpcode()] = orl_43;
  ORL_42 *orl_42 = new ORL_42(*this);
  instructionSet[orl_42->GetOpcode()] = orl_42;
  ORL_44 *orl_44 = new ORL_44(*this);
  instructionSet[orl_44->GetOpcode()] = orl_44;
  ORL_45 *orl_45 = new ORL_45(*this);
  instructionSet[orl_45->GetOpcode()] = orl_45;
  ORL_72 *orl_72 = new ORL_72(*this);
  instructionSet[orl_72->GetOpcode()] = orl_72;
  ORL_A0 *orl_a0 = new ORL_A0(*this);
  instructionSet[orl_a0->GetOpcode()] = orl_a0;
  ORL_46 *orl_46 = new ORL_46(*this);
  instructionSet[orl_46->GetOpcode()] = orl_46;
  ORL_47 *orl_47 = new ORL_47(*this);
  instructionSet[orl_47->GetOpcode()] = orl_47;
  ORL_48 *orl_48 = new ORL_48(*this);
  instructionSet[orl_48->GetOpcode()] = orl_48;
  ORL_49 *orl_49 = new ORL_49(*this);
  instructionSet[orl_49->GetOpcode()] = orl_49;
  ORL_4A *orl_4a = new ORL_4A(*this);
  instructionSet[orl_4a->GetOpcode()] = orl_4a;
  ORL_4B *orl_4b = new ORL_4B(*this);
  instructionSet[orl_4b->GetOpcode()] = orl_4b;
  ORL_4C *orl_4c = new ORL_4C(*this);
  instructionSet[orl_4c->GetOpcode()] = orl_4c;
  ORL_4D *orl_4d = new ORL_4D(*this);
  instructionSet[orl_4d->GetOpcode()] = orl_4d;
  ORL_4E *orl_4e = new ORL_4E(*this);
  instructionSet[orl_4e->GetOpcode()] = orl_4e;
  ORL_4F *orl_4f = new ORL_4F(*this);
  instructionSet[orl_4f->GetOpcode()] = orl_4f;
  POP_D0 *pop_d0 = new POP_D0(*this);
  instructionSet[pop_d0->GetOpcode()] = pop_d0;
  PUSH_C0 *push_c0 = new PUSH_C0(*this);
  instructionSet[push_c0->GetOpcode()] = push_c0;
  RET_22 *ret_22 = new RET_22(*this);
  instructionSet[ret_22->GetOpcode()] = ret_22;
  RETI_32 *reti_32 = new RETI_32(*this);
  instructionSet[reti_32->GetOpcode()] = reti_32;
  RL_23 *rl_23 = new RL_23(*this);
  instructionSet[rl_23->GetOpcode()] = rl_23;
  RLC_33 *rlc_33 = new RLC_33(*this);
  instructionSet[rlc_33->GetOpcode()] = rlc_33;
  RR_3 *rr_3 = new RR_3(*this);
  instructionSet[rr_3->GetOpcode()] = rr_3;
  RRC_13 *rrc_13 = new RRC_13(*this);
  instructionSet[rrc_13->GetOpcode()] = rrc_13;
  SETB_D3 *setb_d3 = new SETB_D3(*this);
  instructionSet[setb_d3->GetOpcode()] = setb_d3;
  SETB_D2 *setb_d2 = new SETB_D2(*this);
  instructionSet[setb_d2->GetOpcode()] = setb_d2;
  SJMP_80 *sjmp_80 = new SJMP_80(*this);
  instructionSet[sjmp_80->GetOpcode()] = sjmp_80;
  SUBB_94 *subb_94 = new SUBB_94(*this);
  instructionSet[subb_94->GetOpcode()] = subb_94;
  SUBB_95 *subb_95 = new SUBB_95(*this);
  instructionSet[subb_95->GetOpcode()] = subb_95;
  SUBB_96 *subb_96 = new SUBB_96(*this);
  instructionSet[subb_96->GetOpcode()] = subb_96;
  SUBB_97 *subb_97 = new SUBB_97(*this);
  instructionSet[subb_97->GetOpcode()] = subb_97;
  SUBB_98 *subb_98 = new SUBB_98(*this);
  instructionSet[subb_98->GetOpcode()] = subb_98;
  SUBB_99 *subb_99 = new SUBB_99(*this);
  instructionSet[subb_99->GetOpcode()] = subb_99;
  SUBB_9A *subb_9a = new SUBB_9A(*this);
  instructionSet[subb_9a->GetOpcode()] = subb_9a;
  SUBB_9B *subb_9b = new SUBB_9B(*this);
  instructionSet[subb_9b->GetOpcode()] = subb_9b;
  SUBB_9C *subb_9c = new SUBB_9C(*this);
  instructionSet[subb_9c->GetOpcode()] = subb_9c;
  SUBB_9D *subb_9d = new SUBB_9D(*this);
  instructionSet[subb_9d->GetOpcode()] = subb_9d;
  SUBB_9E *subb_9e = new SUBB_9E(*this);
  instructionSet[subb_9e->GetOpcode()] = subb_9e;
  SUBB_9F *subb_9f = new SUBB_9F(*this);
  instructionSet[subb_9f->GetOpcode()] = subb_9f;
  SWAP_C4 *swap_c4 = new SWAP_C4(*this);
  instructionSet[swap_c4->GetOpcode()] = swap_c4;
  XCH_C5 *xch_c5 = new XCH_C5(*this);
  instructionSet[xch_c5->GetOpcode()] = xch_c5;
  XCH_C6 *xch_c6 = new XCH_C6(*this);
  instructionSet[xch_c6->GetOpcode()] = xch_c6;
  XCH_C7 *xch_c7 = new XCH_C7(*this);
  instructionSet[xch_c7->GetOpcode()] = xch_c7;
  XCH_C8 *xch_c8 = new XCH_C8(*this);
  instructionSet[xch_c8->GetOpcode()] = xch_c8;
  XCH_C9 *xch_c9 = new XCH_C9(*this);
  instructionSet[xch_c9->GetOpcode()] = xch_c9;
  XCH_CA *xch_ca = new XCH_CA(*this);
  instructionSet[xch_ca->GetOpcode()] = xch_ca;
  XCH_CB *xch_cb = new XCH_CB(*this);
  instructionSet[xch_cb->GetOpcode()] = xch_cb;
  XCH_CC *xch_cc = new XCH_CC(*this);
  instructionSet[xch_cc->GetOpcode()] = xch_cc;
  XCH_CD *xch_cd = new XCH_CD(*this);
  instructionSet[xch_cd->GetOpcode()] = xch_cd;
  XCH_CE *xch_ce = new XCH_CE(*this);
  instructionSet[xch_ce->GetOpcode()] = xch_ce;
  XCH_CF *xch_cf = new XCH_CF(*this);
  instructionSet[xch_cf->GetOpcode()] = xch_cf;
  XCHD_D6 *xchd_d6 = new XCHD_D6(*this);
  instructionSet[xchd_d6->GetOpcode()] = xchd_d6;
  XCHD_D7 *xchd_d7 = new XCHD_D7(*this);
  instructionSet[xchd_d7->GetOpcode()] = xchd_d7;
  XRL_66 *xrl_66 = new XRL_66(*this);
  instructionSet[xrl_66->GetOpcode()] = xrl_66;
  XRL_67 *xrl_67 = new XRL_67(*this);
  instructionSet[xrl_67->GetOpcode()] = xrl_67;
  XRL_68 *xrl_68 = new XRL_68(*this);
  instructionSet[xrl_68->GetOpcode()] = xrl_68;
  XRL_69 *xrl_69 = new XRL_69(*this);
  instructionSet[xrl_69->GetOpcode()] = xrl_69;
  XRL_6A *xrl_6a = new XRL_6A(*this);
  instructionSet[xrl_6a->GetOpcode()] = xrl_6a;
  XRL_6B *xrl_6b = new XRL_6B(*this);
  instructionSet[xrl_6b->GetOpcode()] = xrl_6b;
  XRL_6C *xrl_6c = new XRL_6C(*this);
  instructionSet[xrl_6c->GetOpcode()] = xrl_6c;
  XRL_6D *xrl_6d = new XRL_6D(*this);
  instructionSet[xrl_6d->GetOpcode()] = xrl_6d;
  XRL_6E *xrl_6e = new XRL_6E(*this);
  instructionSet[xrl_6e->GetOpcode()] = xrl_6e;
  XRL_6F *xrl_6f = new XRL_6F(*this);
  instructionSet[xrl_6f->GetOpcode()] = xrl_6f;
  XRL_62 *xrl_62 = new XRL_62(*this);
  instructionSet[xrl_62->GetOpcode()] = xrl_62;
  XRL_64 *xrl_64 = new XRL_64(*this);
  instructionSet[xrl_64->GetOpcode()] = xrl_64;
  XRL_65 *xrl_65 = new XRL_65(*this);
  instructionSet[xrl_65->GetOpcode()] = xrl_65;
  XRL_63 *xrl_63 = new XRL_63(*this);
  instructionSet[xrl_63->GetOpcode()] = xrl_63;
  RegisterSfr(0x81, new SfrSp(*this));
  RegisterSfr(0x82, new SfrDpl(*this));
  RegisterSfr(0xb8, new SfrIP(*this));
  RegisterSfr(0xa7, new SfrSFRPAGE(*this));
}

std::string Alu::Disassemble(std::uint16_t address)
{
  const std::uint8_t opcode = flash.Get(address);

  if (instructionSet.find(opcode) == instructionSet.end())
  {
    throw new IllegalInstructionException();
  }
  else
  {
    return instructionSet[opcode]->Disassemble(flash, address);
  }
}

std::uint8_t Alu::GetOperands(std::uint16_t address)
{
  const std::uint8_t opcode = flash.Get(address);

  if (instructionSet.find(opcode) == instructionSet.end())
  {
    throw new IllegalInstructionException();
  }
  else
  {
    return instructionSet[opcode]->GetOperands();
  }
}

void Alu::Reset()
{
  a = 0;
  pc = 0;
  sp = 7;
  r0 = &iram[0];
  r1 = &iram[1];
  r2 = &iram[2];
  r3 = &iram[3];
  r4 = &iram[4];
  r5 = &iram[5];
  r6 = &iram[6];
  r7 = &iram[7];
  *r0 = 0;
  *r1 = 0;
  *r2 = 0;
  *r3 = 0;
  *r4 = 0;
  *r5 = 0;
  *r6 = 0;
  *r7 = 0;
}

void Alu::Step()
{
  instructionSet[flash.Get(pc)]->Execute();  
}

std::uint16_t Alu::GetPC()
{
  return pc;
}

std::uint8_t Alu::GetSP()
{
  return sp;
}
void Alu::SetSP(std::uint8_t s)
{
  sp = s;
}

void Alu::SetPC(std::uint16_t newPC)
{
  pc = newPC;
}

std::uint16_t Alu::GetDP()
{
  return dp;
}

void Alu::SetA(std::uint8_t a)
{
  this->a = a;
}

std::uint8_t Alu::GetA()
{
  return a;
}

std::uint8_t Alu::GetR0()
{
  return *r0;
}

std::uint8_t Alu::GetR1()
{
  return *r1;
}

std::uint8_t Alu::GetR2()
{
  return *r2;
}

std::uint8_t Alu::GetR3()
{
  return *r3;
}

std::uint8_t Alu::GetR4()
{
  return *r4;
}

std::uint8_t Alu::GetR5()
{
  return *r5;
}

std::uint8_t Alu::GetR6()
{
  return *r6;
}

std::uint8_t Alu::GetR7()
{
  return *r7;
}

void Alu::SetR0(std::uint8_t val)
{
  *r0 = val;
}

void Alu::SetR1(std::uint8_t val)
{
  *r1 = val;
}

void Alu::SetR2(std::uint8_t val)
{
  *r2 = val;
}

void Alu::SetR3(std::uint8_t val)
{
  *r3 = val;
}

void Alu::SetR4(std::uint8_t val)
{
  *r4 = val;
}

void Alu::SetR5(std::uint8_t val)
{
  *r5 = val;
}

void Alu::SetR6(std::uint8_t val)
{
  *r6 = val;
}

void Alu::SetR7(std::uint8_t val)
{
  *r7 = val;
}

void Alu::SetDPTR(std::uint16_t val)
{
  dptr = val;
}

std::uint16_t Alu::GetDPTR()
{
  return dptr;
}

void Alu::SetC()
{
  c = true;
}

void Alu::RegisterSfr(std::uint8_t address, Sfr *sfr)
{
  specialFunctionRegisters[address] = sfr;
}

void Alu::RegisterSfrHigh(std::uint8_t address, Sfr *sfr)
{
  specialFunctionRegistersHigh[address] = sfr;
}

void SfrSp::OnWrite(std::uint8_t data)
{
  alu.sp = data;  
}

std::uint8_t SfrSp::Read()
{
  return alu.sp;
}

SfrSp::SfrSp(Alu &a): alu(a)
{
}

SfrDpl::SfrDpl(Alu &a): alu(a)
{
}

void SfrDpl::OnWrite(std::uint8_t data)
{
  alu.dp = (alu.dp & 0xff00) + data;  
}

std::uint8_t SfrDpl::Read()
{
  return alu.dp & 0xff;
}

SfrIP::SfrIP(Alu &a): alu(a)
{
}

void SfrIP::OnWrite(std::uint8_t data)
{
  std::cout << "SFRIP write " << (int) data << std::endl;
}

std::uint8_t SfrIP::Read()
{
  std::cout << "SFRIP read" << std::endl;
  return 0;
}

SfrSFRPAGE::SfrSFRPAGE(Alu &a): alu(a)
{
}

void SfrSFRPAGE::OnWrite(std::uint8_t data)
{
  std::cout << "SFRPAGE write " << (int) data << std::endl;
}

std::uint8_t SfrSFRPAGE::Read()
{
  std::cout << "SFRPAGE read" << std::endl;
  return 0;
}