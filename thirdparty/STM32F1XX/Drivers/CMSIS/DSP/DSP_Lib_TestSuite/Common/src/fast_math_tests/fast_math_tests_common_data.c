#include "fast_math_test_data.h"

/*--------------------------------------------------------------------------------*/
/* Input/Output Buffers */
/*--------------------------------------------------------------------------------*/

float32_t fast_math_output_fut[FAST_MATH_MAX_LEN] = {0};
float32_t fast_math_output_ref[FAST_MATH_MAX_LEN] = {0};
float32_t fast_math_output_f32_fut[FAST_MATH_MAX_LEN] = {0};
float32_t fast_math_output_f32_ref[FAST_MATH_MAX_LEN] = {0};

const q31_t fast_math_q31_inputs[FAST_MATH_MAX_LEN] = {
    0x414A5524, 0x4CAB5A17, 0x2D6F5B56, 0x7DAF4E3B, 0x29B226EB, 0x41F6F6A,  0x25CE38BF, 0x3A970AFA, 0x3A44382A,
    0x05540F8,  0x3D060524, 0x13D56570, 0x17D7791D, 0x7FE0438C, 0x26741841, 0x40A66E54, 0x218E4386, 0x39FF3726,
    0x0DC177CA, 0x702F2CF5, 0x41142FF1, 0x6C1476AB, 0x15F640DD, 0x662C4E49, 0x38055E7E, 0x770871FE, 0x4F8B5360,
    0x0D1928A0, 0x57647821, 0x258558CF, 0x0C0C604D, 0x50A46C19, 0x66D2370D, 0x50FA359A, 0x36462E24, 0x6CE00F5C,
    0x66D40948, 0x355B5831, 0x3B72150A, 0x1EB61530, 0x73394127, 0x773F26F4, 0x18052980, 0x038D6587, 0x1CF517F4,
    0x22AD1691, 0x7A812473, 0x7CDC7D7F, 0x4A5110D0, 0x6D895BB9, 0x0FD60F35, 0x1A215530, 0x20EB6DDA, 0x3DE62516,
    0x250123E1, 0x5ED813C8, 0x61E175B1, 0x2CBB32F3, 0x6D350907, 0x5B140D7E, 0x6EAE272D, 0x3E221841, 0x418B7B88,
    0x26BB1B80, 0x3CF010E4, 0x24DB166C, 0x79AB7E42, 0x62DF28D1, 0x47004665, 0x63F56FC6, 0x419E0C75, 0x46BE1F38,
    0x243239B2, 0x758D03E0, 0x5CE12926, 0x3F574B74, 0x1F4458E2, 0x71D5639,  0x03A17B49, 0x173A7C76, 0x06EF7531,
    0x48D32F34, 0x7D3E3063, 0x0F2F3549, 0x5C314C9,  0x18CB6B6D, 0x26F83697, 0x447B1E9C, 0x2E323A33, 0x50745715,
    0x01AC5746, 0x655A4E04, 0x4891060F, 0x1DA36B4F, 0x60E6227F, 0x20BF5EB4, 0x50B3225B, 0x40C10544, 0x415656C,
    0x15405EAE, 0x185863E1, 0x236A1C4E, 0x08BD21F9, 0x2ACF7A68, 0x773665E5, 0x4EDF5F66, 0x617A1610, 0x524F4968,
    0x42D006CD, 0x5F000079, 0x24DC2447, 0x6A4F5599, 0x37064D4A, 0x1DE70608, 0x233A2EE5, 0x137E488E, 0x18061B7B,
    0x4079569D, 0x24A817D5, 0x44CE48F5, 0x575F7883, 0x22406802, 0x71AD70BB, 0x1D4A5D79, 0x3CBC7CE4, 0x335840D8,
    0x05792E47, 0x27AD2C05, 0x3D196EAB, 0x331A40AF, 0x33035831, 0x13D93987, 0x7C542094, 0x045F317E, 0x5DC43F8B,
    0x1379650C, 0x5C20193F, 0x7DD50298, 0x1D482B82, 0x4A6B6062, 0x5C8A757B, 0x272917C1, 0x10E16FBC, 0x355A5882,
    0x66F86A35, 0x604555A1, 0x7DF7FBB,  0x758A6216, 0x1A113463, 0x53541BAD, 0x21576756, 0x483B6D8D, 0x1F052FCC,
    0x4EA63DFB, 0x55B84677, 0x7B2E04F2, 0x787A796C, 0x04A12CD3, 0x46029BD,  0x1DB22DD8, 0x1A8C7F28, 0x061E452E,
    0x132D3F78, 0x76525852, 0x73357BBA, 0x6BBB0A58, 0x62536AFA, 0x3F6B65EF, 0x6DC57B58, 0x1EB718CE, 0x66B02740,
    0x5FF60B47, 0x32477B8F, 0x7FF35302, 0x29FD3E40, 0x475A43D1, 0x6FF9528A, 0x2018209D, 0x47E079C9, 0x4CF576D3,
    0x28074E34, 0x5D6F58ED, 0x234045D1, 0x51CE35F9, 0x25297896, 0x644320FE, 0x0F4449A9, 0x54C361C6, 0x701D52F1,
    0x4E094820, 0x718F0810, 0x61540689, 0x79DE5A1F, 0x52865C23, 0x48AC3A4B, 0x6A0C1BE0, 0x21B705DB, 0x7086465D,
    0x1CC10929, 0x1E1D716E, 0x6D231D4C, 0x20495108, 0x38FF1971, 0x149C78D4, 0x441F1E8B, 0x43D95372, 0x69C324B4,
    0x210B7DC9, 0x47815E78, 0x02476137, 0x6163DDF,  0x390D6EC2, 0x2F684E5B, 0x0E680ABD, 0x02232615, 0x12593380,
    0x7B1465FE, 0x065A6957, 0x130F53EB, 0x6D772EF7, 0x10E916B6, 0x63BC7A68, 0x2ACB00BB, 0x651C5590, 0x194714B5,
    0x730904EE, 0x59BB61B4, 0x34867DBC, 0x391C706C, 0x3C164218, 0x28931CD0, 0x129A66AB, 0x13171F4D, 0x62882872,
    0x4B167FD4, 0x66902F4C, 0x7A794932, 0x54B152C,  0x30856EA9, 0x39466D55, 0x36696451, 0x0F5B1E8C, 0x077A3C6A,
    0x51B956B4, 0x367E2D2A, 0x1D2C662A, 0x78FB6880, 0x4E6D40B6, 0x40706FDC, 0x4DF9679C, 0x20306EDB, 0x63812AE7,
    0x255D2748, 0x1B8B617B, 0x3E036FAD, 0x04E444A7, 0x55A37517, 0x669B2988, 0x18FD5E8C, 0x67BD05CE, 0x34BB346C,
    0x76994800, 0x05B958B6, 0x6DFA2FEF, 0x2055B5C,  0x1F843C4C, 0x72721B52, 0x73EF6B86, 0x5FB90B61, 0x43235DAC,
    0x31D424B4, 0x768C0D7E, 0x162F2F9D, 0x7B2A7A99, 0x79392693, 0x442D12C0, 0x0692273E, 0x59A16E80, 0x5D956856,
    0x44E73DAC, 0x0D874532, 0x5F5C1DD0, 0x5D167858, 0x05597EA2, 0x1D821476, 0x59654ED2, 0x594C0DC7, 0x1A873506,
    0x3F693200, 0x7A651AB5, 0x20CC3C8A, 0x1F9E662C, 0x78E7631,  0x2A01DA0,  0x3088472F, 0x12EE0D42, 0x360D4D5F,
    0x73337E48, 0x0D634C06, 0x233A0ACB, 0x706651ED, 0x7AA54079, 0x262239D1, 0x3EBB6BB6, 0x225A4F3D, 0x32581A06,
    0x6E6F5780, 0x577377C7, 0x75ED1DDC, 0x10DF2D15, 0x3C7929BC, 0x37175917, 0x354E381C, 0x762A2DD7, 0x76435AC1,
    0x73BB749E, 0x52FE4E7E, 0x6C8140F4, 0x57694875, 0x12D30822, 0x474227CF, 0x37926D98, 0x121C7E24, 0x204E1EE7,
    0x58C6268,  0x2152080,  0x316C3323, 0x7AB14A31, 0x61C13C03, 0x7D8E74F1, 0x73F446D0, 0x6C6C6A0A, 0x3BFD79FB,
    0x67242969, 0x3E5524EB, 0x0FF5534,  0x52F05F1C, 0x17102DE3, 0x540F4A21, 0x798468E7, 0x419545EB, 0x193F7880,
    0x2B246B20, 0x408A2BC4, 0x4BF66A49, 0x40894C55, 0x4CAA6398, 0x247856E9, 0x2F2A647D, 0x22F55D33, 0x70D37915,
    0x50634C72, 0x5983671,  0x2BCC5AF8, 0x1A77D48,  0x411B5CFA, 0x71074D7E, 0x3A6B3593, 0x61425F05, 0x6271012A,
    0x5B830310, 0x3D8418CA, 0x10A50792, 0x239F7137, 0x213D5071, 0x7F9930D4, 0x2462664F, 0x54180F8E, 0x291505BA,
    0x6586387A, 0x144B2C12, 0x18E425C7, 0x3AA43373, 0x18F0503C, 0x19462AC0, 0x58B452EF, 0x72473895, 0x26BF5435,
    0x6DA553B,  0x60912FA6, 0x5C337331, 0x3D93CD7,  0x4D035752, 0x20691929, 0x389962F9, 0x36E701E9, 0x758B642C,
    0x5FCA69E3, 0x596027F4, 0x2D5A2FD0, 0x5F18324A, 0x3DB165AA, 0x76BA3876, 0x1BC21AF6, 0x3CC10841, 0x73A60174,
    0x625B7F58, 0x67C57724, 0x4458653C, 0x61573095, 0x2B370837, 0x03DF6CE3, 0x5D086EFA, 0x3F5227C2, 0x191B4785,
    0x60843D82, 0x30DE11F1, 0x105E226C, 0x6E1C7AA2, 0x47AA5D14, 0x36676D03, 0x3B8D4DF6, 0x7372694,  0x409521DC,
    0x744206A,  0x4722023F, 0x2BE46AD5, 0x63E11D76, 0x4A4A09AB, 0x5CF252B9, 0x31586916, 0x4DFD7D84, 0x32037634,
    0x2D7329D4, 0x4524582F, 0x2E5366C1, 0x3B0E019B, 0x38530C6A, 0x6A2542D,  0x0A6A00E5, 0x119725CC, 0x54065347,
    0x1B6F7AF1, 0x6CCF71F1, 0x181117F2, 0x71674A76, 0x74F43880, 0x77A55F47, 0x59EA5B62, 0x4A331D95, 0x3CBB276F,
    0x245C4D50, 0x4718D5,   0x07CE05D1, 0x60D47AD5, 0x25CA1C40, 0x30061766, 0x669B39DF, 0x3D5F1320, 0x19306AD3,
    0x28B30325, 0x0DD090F,  0x6A6E6F37, 0x2DF16F66, 0x2B514C7E, 0x31101C58, 0x7D4847FC, 0x515341CA, 0x77AB0EA6,
    0x41320DAF, 0x3AF8531E, 0x24B31611, 0x6D377331, 0x7A832A22, 0x222511C7, 0x722D1F89, 0x3B194F18, 0x261B0A4D,
    0x43F676DB, 0x4F8C6D61, 0x190F2250, 0x202E72A9, 0x560D4EA2, 0x308E67B4, 0x36746663, 0x17CC3852, 0x27EB2EAC,
    0x7FDE0AA8, 0x264719A,  0x23261EDD, 0x3C0B339E, 0x06284D40, 0x48D82ECB, 0x24D44CF8, 0x43631B91, 0x4BF04248,
    0x36497B9B, 0x68273C58, 0x630B7AF9, 0x20CC3F26, 0x6C3B7B71, 0x574433ED, 0x7A2552F6, 0x4CDE642D, 0x565B0142,
    0x26F9207F, 0x67A207BE, 0x5B506684, 0x44DA4780, 0x11756A0C, 0x156104AF, 0x415561B0, 0x6E3A6886, 0x1DBA1EA2,
    0x542359C8, 0x4C024E22, 0x758F052A, 0x1DD6395,  0x2D194BAD, 0x616475A1, 0x42084602, 0x09C274AD, 0x13CB5562,
    0x57FE2D5B, 0x607A4EE5, 0x16723A91, 0x4F624CCF, 0x2E5E24A3, 0x28FE6FAF, 0x3DDA6EF4, 0x32AF540C, 0x19A57B3B,
    0x5D1D73A3, 0x23424B3E, 0x278445F5, 0x53971C3B, 0x427D7943, 0x5221358C, 0x26CE1A5E, 0x7B506CA4, 0x3B86636E,
    0x60831F6D, 0x45E142F3, 0x21B77B04, 0x7BB65E0C, 0x78B80F5E, 0x7D8D172B, 0x3BF33A90, 0x2D572D9,  0x2B5B4920,
    0x36A05E01, 0x52745306, 0x47C64855, 0x1CAA669B, 0x304A2641, 0x4D6B1760, 0x3E176D79, 0x523241B0, 0x24A67957,
    0x4BDE76AF, 0x4E5F1493, 0x4C215DA5, 0x33A052B,  0x1A4D00C2, 0x40AE6BCA, 0x390D106B, 0x69E86018, 0x5AF356CF,
    0x63561D4,  0x44F31C6,  0x14B6299B, 0x0D2E25F0, 0x4CBF132A, 0x45AC18B6, 0x2227567D, 0x06B54E2F, 0x26344534,
    0x22C515EC, 0x2442370D, 0x6C3721C6, 0x34EF687D, 0x1C06323A, 0x6AF36A60, 0x60396F52, 0x6AE70AA1, 0x49D06CBC,
    0x6F9576C8, 0x584C4258, 0x3A9A27BB, 0x66DF0D47, 0x1D4804EA, 0x57DD1E67, 0x789C7895, 0x75336111, 0x25C122C8,
    0x62742114, 0x4FBF6D26, 0x3F9F6482, 0x66F02CD9, 0x11083202, 0x499E2618, 0x7EBC1351, 0x440112F1, 0x49DF7BC1,
    0x3BF45C25, 0x31BA7FA0, 0x61AF1AED, 0x6B1F7D29, 0x2D865294, 0x63E01129, 0x7E9E77A5, 0x100435D7, 0x1FE3A71,
    0x08597C81, 0x722849FA, 0x31C520AF, 0x7BA178DC, 0x7F102D31, 0x5CA07864, 0x150E6F98, 0x02C34882, 0x5D041F11,
    0x0C613C57, 0x53984FD1, 0x426F38AD, 0x55992B1D, 0x7AFA078D, 0x2B253413, 0x594B32CF, 0x32887E38, 0x28933B46,
    0x1A0B4168, 0x291B4A94, 0x653A5E8D, 0x21746BBE, 0x5EFE6415, 0x30DA429C, 0x50C5640C, 0x34711AA4, 0x529C67A6,
    0x105957CD, 0x4D287499, 0x03CA0AA7, 0x28385832, 0x25A04A02, 0x420D47A4, 0x35627556, 0x4BC11E4C, 0x59E215C7,
    0x27E838B4, 0x458612F4, 0x22827F6F, 0x449D4DBA, 0x679B7362, 0x4E495845, 0x4FD270D1, 0x395E76A0, 0x375A655E,
    0x12E2058F, 0x73F970CA, 0x61EF73B3, 0x51FF5362, 0x67410345, 0x7FDA0B3B, 0x221962E8, 0x17AB6543, 0x26557412,
    0x4B30084D, 0x268E191D, 0x7E0D13DF, 0x73EF127D, 0x4DEC5DB1, 0x77FA745F, 0x56002898, 0x12DD0A40, 0x157F6DDF,
    0x42A55F8E, 0x43597924, 0x7B630C3F, 0x338B6B58, 0x32945F75, 0x4FA23A0E, 0x036E38C0, 0x33B18FD,  0x06114337,
    0x24660ACB, 0x19BB02F0, 0x124C0A47, 0x3A951701, 0x01155ABF, 0x0C612D71, 0x36074CA7, 0x51660C41, 0x635F58C7,
    0x7FC2002D, 0x0E6A7CF3, 0x65B07D07, 0x015F6A6B, 0x791B70DD, 0x6E475719, 0x424314C7, 0x68426EB,  0x71942FEE,
    0x464A2F52, 0x677579FD, 0x6BA775AE, 0x1F66EFF,  0x1A795237, 0x78D9545F, 0x1D0B344D, 0x3BD34AB7, 0x2F85312A,
    0x16C542AD, 0x3990185D, 0x08DF3351, 0x02811AA5, 0x6D351F41, 0x4066269D, 0x06B660BF, 0x6EDB4768, 0x5DD70CF0,
    0x35D74F6E, 0x689E220C, 0x11431687, 0x147C49C9, 0x385762BD, 0x302F0AE4, 0x1DAB67F8, 0x483256C9, 0x37D50FCB,
    0x4EA82711, 0x4D7B2C98, 0x19DB78BC, 0x58DE0DC2, 0x6AFF7E7B, 0x37621C93, 0x792C6E19, 0x77001192, 0x7F88439D,
    0x2E196A66, 0x6C71378C, 0x6AF43B3A, 0x7C16225E, 0x6687337,  0x4BEE1608, 0x6D5B5552, 0x345D4590, 0x681209CC,
    0x7B242819, 0x508A1416, 0x19880FE3, 0x1FC7288A, 0x24BD0502, 0x6A1D1678, 0x20E6CA0,  0x59BE2057, 0x5ADE11EB,
    0x5EA8649D, 0x7A200E6F, 0x1149481D, 0x72281E93, 0x0A5B0451, 0x67312D58, 0x63B849F1, 0x52217960, 0x7CDF59F3,
    0x33C775C0, 0x1EBA0799, 0x7DF1506,  0x34E96110, 0x38FC73E3, 0x5EA059B2, 0x022936EA, 0x316406F6, 0x43911185,
    0x6C0D10F3, 0x1C6F3DF8, 0x38DB12A9, 0x5CD41244, 0x2C9F0A7B, 0x5F4A315F, 0x77CE1C66, 0x4C800860, 0x318D53E0,
    0x7105420D, 0x575361F2, 0x750810BA, 0x217E4CA5, 0x2010140,  0x4D884763, 0x42BB0DA7, 0x32D53A74, 0x141C6CD4,
    0x087F5FC3, 0x464B53,   0x2D2A05F6, 0x15532B45, 0x5D5C3CE1, 0x3EB9216A, 0x2214611B, 0x1FC52C5F, 0x11AE5DD7,
    0x20B925A9, 0x7C640AF4, 0x740009AC, 0x6D0E0321, 0x38E6A61,  0x09104544, 0x474F26C8, 0x15254CF3, 0x341A6B59,
    0x661904CE, 0x598B2197, 0x2412659D, 0x61976DD4, 0x329B3E16, 0x08FD1FB0, 0x304006F3, 0x3456309,  0x55CC15F1,
    0x59DA7630, 0x5C801335, 0x0036D52,  0x353775A5, 0x299476EB, 0x75280568, 0x766F5264, 0x2EA233A6, 0x647619F3,
    0x7FB30C7A, 0x1BC03B9,  0x36BC3061, 0x3F30596E, 0x3E2A527B, 0x0AC04220, 0x641979A3, 0x1ECC3B89, 0x21447BC1,
    0x4E8F2E26, 0x0C5A1D90, 0x299E5467, 0x57C947E3, 0x1D4865ED, 0x76F31C3D, 0x4EE81CDF, 0x3479195E, 0x6FFB3AE1,
    0x5C82398,  0x300F7364, 0x47940AFA, 0x3B853E3E, 0x598C440D, 0x224A3D89, 0x3A674204, 0x22880A38, 0x2E77F2D,
    0x22841C9C, 0x4F0609C3, 0x1FE90922, 0x09335017, 0x2D6B69A7, 0x7EDB63F9, 0x099A74EF, 0x1F9F1B40, 0x24BE17E8,
    0x251D2F7A, 0x16AC50D3, 0x28D7ED6,  0x6D193443, 0x76156F1B, 0x30DF6A4E, 0x64FF6794, 0x63DB2C9A, 0x74353022,
    0x556E025C, 0x23802AF9, 0x425018A4, 0x675A18BB, 0x70B227B9, 0x7FB01BF,  0x63E7910,  0x6C661591, 0x65745D2B,
    0x4F6E379D, 0x52B32FAC, 0x1E6A1101, 0x1DE22385, 0x2338191F, 0x469704B6, 0x4BAB4599, 0x54EB4809, 0x78393E6D,
    0x550017DD, 0x39B120E1, 0x288D52D3, 0x2D52668C, 0x20D22A68, 0x4E1207D1, 0x3FCC0EFE, 0x47F37E64, 0x25177A90,
    0x34BF5D4D, 0x5A8D3DCE, 0x6F7275A8, 0x6BEA2655, 0x2A1810FC, 0x64DB593A, 0x0A4D4BC0, 0x2C402E93, 0x71C077F9,
    0x6F0C4577, 0x70412414, 0x752F1DC1, 0x582E38EA, 0x2C455F7B, 0x4DCD4EDB, 0x12BC2696, 0x7B037135, 0x4FCA1F8C,
    0x3D5E75F6, 0x502F41B0, 0x361653F1, 0x2E5B0E31, 0x20266B19, 0x57E703D7, 0x467B3E00, 0x47032BA3, 0x1F776B9C,
    0x62570A84, 0x7EC75B48, 0x1BD5012,  0x7D0A2D5D, 0x7FCC29F2, 0x291304B6, 0x19D558ED, 0x47551C8,  0x7D12738F,
    0x3ADE0892, 0x5F741997, 0x25D2E2F,  0x2B9F2269, 0x5C134FED, 0x15E92399, 0x54437F4E, 0x272D32AB, 0x56186AA1,
    0x7E4D355C, 0x234D7836, 0x2A871760, 0x4637A94,  0x2C183207, 0x5FC78B3,  0x7F10621E, 0x276966B2, 0x6C9F4A11,
    0x4E3F182C, 0x62BA2EF5, 0x25F239CD, 0x73D63FED, 0x636E1F5E, 0x0AC15A0E, 0x3F3D33EB, 0x738326EA, 0x35C366B1,
    0x4D476E86, 0x02F63208, 0x711A1FC1, 0x426A4396, 0x7E4D1B93, 0x75E46DB7, 0x2F3C44A7, 0x51A56F5C, 0x7AD2463D,
    0x0A5639CA, 0x49952C78, 0x4C4B64F6, 0x3AFE7F8D, 0x66993D04, 0x43867F37, 0x4BC146C2, 0x55A875EC, 0x681A1A75,
    0x30A67E1B, 0x4A4A7D0C, 0x20F77993, 0x1891805,  0x738976AD, 0x542667D6, 0x3C5C6EBF, 0x4499187F, 0x2BF17C97,
    0x447C317F, 0x68D8419C, 0x7AAB6456, 0x421B4F29, 0x76740F9C, 0x09163B8D, 0x3D72AAB,  0x1AD54DD7, 0x754946EE,
    0x7317342B, 0x218546D4, 0x10563DA7, 0x54BB4CCE, 0x0CE63E46, 0x5D146234, 0x33BE6C63, 0x325044E5, 0x09D72335,
    0x07C36BA,  0x365530CC, 0x2DFA448C, 0x1663516F, 0x59B00AA,  0x150274EA, 0x12532D4A, 0x3CEF002D, 0x492F3DA5,
    0x263A2574, 0x6F8005C2, 0x14A10651, 0x2F627ABA, 0x68293238, 0x26987646, 0x52590516, 0x10144D36, 0x59B151B9,
    0x2B2A4F05, 0x53953699, 0x27851C75, 0x180646F3, 0x2E970306, 0x32843145, 0x18F4FE8F};

/* The source data is random across the q31_t range. Accessing it by word should
   remain random. */
const q15_t *fast_math_q15_inputs = (q15_t *)fast_math_q31_inputs;

const float32_t fast_math_f32_inputs[FAST_MATH_MAX_LEN] = {
    -1.5E-07,   5.0545058, 6.1958757,  0.1884450, 3.3656774,  0.5471223, -5.0396892, 6.2149808, 0.4206357,  5.9024140,
    0.1142128,  4.2966847, -4.9243615, 3.3560853, 5.5628775,  5.6486144, 3.9328821,  0.8662564, -1.3684878, 1.1444261,
    0.2627620,  0.6719343, 3.8732286,  5.9040643, -2.2271110, 2.5800587, 6.1848498,  5.9412493, 4.2514839,  6.2096863,
    -4.8181437, 2.1155439, 4.1618680,  1.5341357, 1.8567268,  4.2736867, -3.3165594, 2.5861183, 3.7864876,  4.7156566,
    3.6664471,  3.4670146, -3.6666823, 3.2158594, 0.5189454,  4.5211925, 6.2590334,  2.2276047, -6.1025991, 2.1768018,
    5.5703194,  2.8569321, 2.5976403,  1.3680509, -0.7895111, 1.9409676, 4.5622487,  4.9189303, 4.3591961,  0.0615894,
    -5.2980657, 5.7951829, 4.8440482,  0.2680398, 2.3762136,  4.4254964, -4.5836656, 1.4091744, 1.6905207,  4.2287795,
    3.0001720,  3.9189258, -1.4856273, 1.1129014, 5.2128031,  4.8187110, 5.8715002,  0.6778860, -1.1449692, 0.6226340,
    3.0772767,  1.2141962, 5.6290528,  0.6225986, -0.2775005, 3.5015887, 4.8537297,  1.9599772, 1.1245801,  2.1297213,
    -1.3203840, 3.2053828, 5.6948550,  3.9516457, 0.6379562,  2.4558128, -0.3431663, 3.1496534, 2.7125841,  6.2678565,
    5.0994494,  3.0514394, -5.6199810, 0.8642307, 2.4504731,  5.8267510, 5.7647838,  4.4835177, 3.8851284,  2.1569414,
    5.8812331,  0.7839784, 4.5904032,  4.0619375, 5.2348483,  2.5024810, 4.7112719,  5.2478452, 2.0260784,  3.4699621,
    6.1520498,  3.4514073, 2.0761128,  3.8922546, 2.2659464,  4.7532896, 2.6006151,  3.0934955, 4.3652005,  6.1118673,
    2.0593452,  5.2640727, 4.6437278,  5.9952549, 0.2005758,  2.2422740, 4.1635768,  1.7687265, 1.4475395,  4.4681525,
    3.9243074,  3.7109036, 4.1496541,  0.2987948, 2.1914796,  2.8358565, 1.5136507,  4.4927603, 5.3795520,  1.7687650,
    4.5933278,  0.8655898, 5.2572843,  0.8708603, 3.6958286,  2.3006310, 5.0690197,  3.1653480, 3.0762120,  5.5106597,
    2.2188555,  2.8239372, 6.0540393,  0.2657649, 6.1132775,  1.1888217, 4.1916405,  3.6847088, 4.2418564,  2.2683684,
    3.8973243,  5.0966113, 0.1209983,  0.5269928, 6.1248595,  4.0925498, 1.4529100,  2.5352096, 0.7666775,  1.6866509,
    1.6200953,  2.0839142, 0.9565145,  2.1865966, 0.7644026,  5.5552975, 0.5923686,  5.8436176, 2.5071164,  0.2978322,
    2.1511962,  4.6242118, 4.9931353,  3.4237447, 4.3116692,  5.6148598, 0.3442670,  1.9079607, 0.2902301,  1.2282167,
    4.5249352,  4.5349096, 5.5153742,  3.6595342, 0.4441228,  5.7977751, 5.0288862,  1.7966571, 3.4159368,  6.1875316,
    4.4967379,  5.2714014, 2.7222564,  2.9570223, 3.5230663,  1.6907520, 4.7062218,  3.1660203, 4.0640250,  1.9336225,
    0.8716326,  2.9881129, 2.2773988,  4.9518627, 4.9027432,  4.2003861, 0.8388295,  0.1354396, 3.5175829,  1.8901016,
    5.9024853,  6.1631993, 1.8008890,  5.0317023, 5.6304337,  3.7543702, 5.5544410,  5.9296402, 3.4504620,  4.5765894,
    3.6238793,  0.1624673, 2.8056369,  4.0608350, 3.2748147,  2.3393094, 5.8881908,  5.2121085, 5.3349614,  2.3407017,
    3.7270886,  5.4824095, 5.8653636,  4.2000849, 1.2992148,  4.1082644, 0.4527132,  2.5555406, 4.1904544,  5.8667713,
    5.0953493,  3.0445066, 4.7547955,  2.6203864, 6.1059115,  6.2076281, 5.4295991,  2.4434288, 2.8572272,  1.5499814,
    4.9286757,  5.5470323, 5.7410198,  3.5078076, 3.7627993,  0.9354200, 5.6530665,  2.8299063, 1.2922774,  5.6526739,
    4.7914663,  5.5448250, 1.7903950,  4.2300036, 4.1737937,  0.7716694, 2.5592571,  1.7296789, 4.5029688,  1.7805566,
    5.6309835,  5.1935484, 2.4506089,  3.1284165, 4.3655898,  5.2424950, 3.8304163,  3.6111801, 2.0485834,  2.8678003,
    4.4849099,  5.5568808, 4.5292698,  0.1169475, 4.2397456,  2.7552322, 2.7509053,  0.7353640, 5.1187960,  2.0411269,
    1.5470969,  2.1533307, 2.3605433,  3.4340988, 3.5306485,  2.4870244, 2.5015301,  3.2381477, 4.1313862,  5.9747764,
    4.5386496,  2.5137752, 5.2268018,  0.8440727, 0.3799239,  0.5293398, 0.0000000,  2.0371338, 1.8958053,  0.0733938,
    3.3923238,  0.5992443, 0.9205800,  3.9655772, 5.3992694,  6.1212150, 3.5866836,  6.2633946, 3.4780043,  3.2387210,
    2.0777367,  2.7017810, 3.0901098,  0.4463392, 5.5778300,  0.4061048, 2.7406309,  5.1938664, 2.4789345,  3.8545764,
    5.1436714,  5.5683790, 5.8503469,  1.1987353, 1.6247202,  5.6414565, 3.7282025,  3.1657206, 3.8503962,  5.1485818,
    3.3419582,  1.2696753, 2.8518968,  2.6886436, 6.0698884,  3.8959208, 4.3692639,  4.5249277, 2.1796068,  3.2483466,
    3.4978155,  0.9832885, 3.5315023,  4.3655778, 2.6794992,  5.2544420, 4.5954405,  2.2621418, 2.8539005,  2.4277593,
    4.8729535,  4.6135614, 2.7035154,  4.3589760, 5.9389515,  4.9274787, 4.4332387,  0.6869673, 2.4500066,  3.7127639,
    2.8863700,  0.3162955, 1.4368865,  5.2413645, 0.0982985,  5.4268554, 0.4905223,  4.2037186, 3.1429204,  1.3696954,
    3.5915675,  0.7677371, 4.2170618,  3.7673071, 0.3517086,  0.3540136, 0.9581898,  0.1232828, 2.7342886,  5.2290017,
    3.8791769,  3.2680695, 5.4278441,  0.6138541, 5.7054603,  0.6786889, 3.2483864,  0.8994758, 3.5146290,  0.0287746,
    4.8172051,  5.3325973, 5.7605579,  6.2013046, 3.1738449,  1.7053924, 0.6330341,  3.1909083, 3.6794907,  4.7933610,
    0.5212697,  4.1569315, 3.2482749,  1.0747264, 5.8971330,  3.7101152, 2.7685894,  5.9182512, 4.1212281,  2.8396586,
    5.2759745,  3.3465722, 3.4801751,  4.2729777, 2.3071222,  1.5035072, 3.6374836,  5.4468120, 2.5558538,  0.7075818,
    2.7887656,  1.8861142, 2.5219880,  5.2361777, 2.5360737,  2.4515477, 2.2647672,  0.8812504, 1.6344462,  0.5454754,
    2.6979830,  1.6165554, 1.8695956,  2.6694641, 0.7490013,  3.1105972, 4.4384875,  1.5304166, 4.9327408,  0.4655185,
    2.4748426,  0.0213259, 1.3865538,  0.0081717, 1.1886509,  0.8952537, 1.6843712,  1.0988793, 0.8711572,  3.7629093,
    5.6615138,  5.9022971, 1.3897429,  3.0327137, 2.3625475,  3.2910070, 1.6642436,  0.4295011, 2.7415239,  1.0923508,
    0.1640358,  5.9984205, 2.7055177,  6.0416507, 4.7903915,  0.0461730, 4.2728088,  4.4356194, 4.0534637,  3.4702651,
    1.3704176,  4.8529200, 1.4327442,  2.3302118, 5.5978709,  5.3807748, 2.5285646,  1.9981730, 3.8241692,  5.7189253,
    5.7120324,  3.7170973, 2.0896078,  5.3599569, 2.7796679,  5.6822331, 0.2084724,  3.3453343, 4.5018856,  1.1265867,
    2.1144987,  1.1794352, 2.0227281,  2.5375066, 3.4467437,  0.3062336, 3.4729184,  1.7266910, 1.5174002,  1.5277262,
    0.9686124,  6.0093412, 5.8789338,  5.1441345, 4.5758041,  1.1046577, 2.2642776,  1.1862024, 0.0075297,  1.9881224,
    4.3958232,  3.9285942, 3.4121603,  2.7585521, 1.8059588,  3.1520171, 4.7849358,  4.7903511, 3.6194660,  4.6977042,
    4.0560129,  0.7742111, 3.1692252,  2.1819072, 0.5789810,  0.9289656, 1.2451370,  4.2239985, 2.7112647,  4.3630684,
    1.6134250,  0.0613154, 3.3444332,  1.7554715, 5.9453394,  5.6953510, 2.4673100,  0.1561700, 4.2187618,  5.2600982,
    6.1041123,  0.3577199, 2.8294680,  3.6597688, 4.3142726,  4.5203293, 4.0843265,  4.5673388, 2.3489542,  3.6541880,
    0.7295941,  0.3622530, 6.1560465,  1.7896003, 3.7383338,  6.0454361, 1.1672793,  1.2129049, 2.1466132,  5.8615704,
    2.4546365,  1.7166712, 0.9547117,  2.4951084, 2.3544507,  0.8238180, 2.7334414,  0.5749942, 3.8618151,  0.0689837,
    3.6019012,  4.9620190, 1.4788531,  2.8149909, 3.5773830,  0.3857966, 3.1182750,  4.0357856, 1.3902536,  5.2593808,
    6.1014456,  5.3179177, 3.1792883,  1.7522271, 4.6911344,  1.4886775, 6.0151778,  3.8972087, 3.7715583,  1.0845061,
    0.5676653,  1.6038597, 5.3945577,  5.7244031, 4.3959286,  4.5564551, 1.4444168,  3.6194506, 5.0933266,  2.5374227,
    6.2105471,  0.5654792, 2.0165320,  3.2132771, 0.3808010,  4.5596317, 3.4969429,  3.3260664, 5.2149334,  5.3957421,
    4.9576149,  1.9970040, 2.8413032,  4.7263877, 0.6902815,  0.6895316, 1.6957291,  3.2963937, 6.1113470,  4.4636294,
    1.9594738,  1.8312791, 5.3429527,  5.7280497, 4.0166905,  1.6045389, 0.5571039,  5.2669152, 3.6738954,  5.9571429,
    0.3834561,  3.6734096, 1.7913869,  5.2007946, 1.2000032,  2.7804978, 2.4718774,  5.1935175, 4.2529065,  1.3044083,
    1.9987109,  0.8407592, 4.2189258,  3.5876427, 1.0666779,  0.9277486, 2.9912971,  5.7057758, 3.4694180,  0.2069675,
    0.3384307,  5.0583614, 2.8360719,  2.4042372, 4.9614777,  2.2888819, 3.3448533,  4.4714710, 5.4756485,  2.0652177,
    4.0848120,  6.1250762, 0.4773170,  3.6883502, 2.6005256,  1.9423615, 1.6577182,  4.7674690, 6.2531264,  1.1722630,
    4.9080805,  1.2302350, 6.2351753,  5.0407581, 2.6654950,  4.5795867, 3.1312479,  5.0830358, 2.2400117,  0.4602021,
    3.7133088,  5.7188788, 1.2174673,  2.7166470, 4.7071094,  0.2462034, 5.9459353,  4.7983010, 3.5111731,  1.1551193,
    3.1287047,  3.2537199, 6.2470131,  5.3711915, 6.0469623,  4.2659122, 2.5352740,  5.8746469, 3.0126903,  1.4563896,
    2.4899651,  4.4301324, 3.5095299,  4.7540509, 6.2547920,  6.0471349, 3.3619258,  6.0561746, 0.7264988,  0.3232592,
    1.9122808,  3.6454528, 3.3361480,  5.6624574, 3.3963785,  2.7142142, 3.4096772,  4.4762342, 0.1047703,  5.0323343,
    0.8954125,  3.0063438, 1.6137441,  2.3190715, 4.1579916,  1.0656836, 1.7516517,  1.2454643, 1.2256706,  2.0535941,
    5.5313259,  2.9600203, 2.5382144,  1.1261446, 6.0879353,  2.5601199, 5.3060708,  3.8662016, 2.3663172,  5.5114955,
    4.9313732,  2.9213939, 5.1143679,  5.6450910, 2.6969853,  2.1006537, 3.7488443,  5.6673754, 4.4112136,  2.3716204,
    4.6178643,  5.9948046, 3.4105954,  3.3935850, 1.9547595,  0.4475800, 1.1434170,  0.5842667, 2.9121888,  0.0586379,
    5.7492774,  4.0384655, 0.0089162,  0.1909163, 1.3098570,  2.8586366, 0.7996361,  0.0543350, 4.5683759,  2.2249794,
    4.9036865,  2.7435946, 2.7429546,  0.3092155, 0.3118464,  0.5723993, 3.7324447,  1.5147758, 5.2864780,  5.3860266,
    6.0545540,  3.0718480, 1.3842492,  1.4213108, 3.3727372,  4.7884765, 2.1838288,  2.8980046, 4.0169897,  5.7637923,
    1.0151904,  4.4964699, 3.6300404,  2.7224978, 5.5558613,  2.4696170, 1.1245340,  3.9793522, 3.9207111,  2.0605178,
    5.0451799,  6.2799046, 6.1636676,  0.7981966, 1.4592079,  0.1484872, 3.8166117,  0.6962355, 2.5601436,  5.5548184,
    3.4440198,  2.3185147, 1.3090764,  2.7705283, 6.0079576,  0.7792778, 2.9578927,  5.3840384, 0.2726304,  4.3456090,
    6.1511471,  1.7798247, 0.8405677,  4.3057392, 5.7142715,  3.8382030, 5.6547587,  1.2153801, 4.7401894,  2.1756202,
    2.6303011,  0.9784166, 5.1459324,  3.9265103, 4.6405120,  5.0586705, 0.4223724,  5.9739917, 3.1263686,  4.7447217,
    4.6646686,  5.2221411, 0.9833301,  2.8733554, 3.8836400,  5.8570808, -5.2470141, 5.6261119, 3.6600718,  3.6615062,
    5.3716581,  0.2190677, -5.5632585, 2.5618482, 0.2285950,  4.6881858, 0.9728179,  0.9042027, -3.8073530, 1.5989503,
    2.0367209,  2.5245268, 2.5533189,  2.4265105, -3.8314979, 1.0486053, 1.1818174,  0.5945707, 2.0306392,  4.8355201,
    -1.4710068, 4.6518534, 4.3531065,  5.1778361, 5.2023364,  1.8432851, -1.9438243, 3.2862931, 2.0439139,  5.2266206,
    5.0912323,  3.4997233, -1.6522518, 4.2761236, 1.4680860,  2.8678051, 2.4163051,  3.3841326, -6.2310582, 4.7451897,
    6.1603795,  1.4751828, 3.3210347,  0.3231823, -4.7555888, 3.7823504, 5.3857498,  6.2095284, 5.8401232,  2.5730582,
    -0.0021455, 3.3984387, 1.3052100,  1.3777994, 2.0471011,  0.6028680, -4.6968925, 4.7030205, 3.4136510,  2.1245480,
    5.2297066,  3.4719134, -6.0164208, 5.6098372, 2.2399783,  3.4331443, 2.1782657,  3.9131853, -5.0053405, 4.6864702,
    0.7887674,  5.1672539, 0.1580253,  2.6039335, -4.5955687, 4.9095176, 2.3077255,  4.6801428, 5.6062801,  1.5243220,
    -0.8142818, 1.4141432, 2.1992023,  1.8038058, 5.8275790,  0.3224138, -3.7238350, 1.0235240, 5.2678588,  1.0528164,
    3.1554195,  6.2789723, -2.2330890, 0.2957980, 1.3424690,  2.4996969, 2.0964990,  1.4426353, -5.8818165, 4.2926017,
    6.0451393,  2.7518666, 5.9083095,  0.0366581, -3.8346722, 5.0333074, 1.4638661,  5.8588735, 4.7957215,  5.1927356,
    -3.6031780, 4.9799375, 2.0674268,  1.4040530, 1.9627813,  3.6726693, -5.2145043, 1.8250297, 2.5293238,  5.4164658,
    3.8625225,  6.2278165, -1.2798778, 5.1975080, 4.2465638,  1.5641957, 2.9894493,  2.5074636, -3.7663816, 5.0298329,
    0.6601666,  5.1612735, 5.2847013,  2.2274284, -2.7022061, 3.5954850, 4.4034117,  4.6650751, 4.7619266,  2.4449681,
    -2.6973871, 6.0088907, 3.6000853,  5.3389611};
