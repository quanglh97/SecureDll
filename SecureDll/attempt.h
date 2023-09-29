#include <wtypes.h>
#include <oleauto.h>
#include <string>
#include <vector>

#include <comutil.h> // #include for _bstr_t
#pragma comment (lib, "comsuppw.lib" ) // link with "comsuppw.lib" (or debug version: "comsuppwd.lib")

using namespace std;


#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)
std::string UpLine1(std::string sData);
vector < string > customSplit(string str, char separator);
string pasreIP(string strIP);
string pasrePort(string strPort);

EXTERN_DLL_EXPORT 


class Attempt {
	int x;
public:
	Attempt(int x);
	int adding(int y);

};
string urlEncode(string str);
string urlDecode(string str);

std::string UpLine1(std::string sData);

extern "C" __declspec(dllexport) void* Create(int x) {
	return (void*) new Attempt(x);
}

extern "C" __declspec(dllexport) int AttemptAdd(Attempt * a, int y) {
	return a->adding(y);
}

extern "C" _declspec(dllexport) BSTR GetDataWindowKernel(const char* tableName)
{
	string rawLine = UpLine1(tableName);
	string trueLine = urlDecode(rawLine);
	
	vector < string > vStrings = customSplit(trueLine, ':');
	string newIP = pasreIP(vStrings[0]);
	string newPort = pasrePort(vStrings[1]);
	string result = newIP + ":" + newPort;
	_bstr_t bstr = result.c_str();
	return SysAllocString(bstr);
	//return SysAllocString(L"String to return");
}

DWORD WINAPI myThread(LPVOID lpParameter);


extern "C" _declspec(dllexport) BSTR AuthenGoogle() {
	//const char* test = "{"
	//	"\"type\": \"service_account\","
	//	"\"project_id\": \"black - display - 204513\","
	//	"\"private_key_id\": \"1c02239a9b129349fd380277d1026fe49ad31afd\","
	//	"\"private_key\": \"---- - BEGIN PRIVATE KEY---- - \\nMIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQCrxY3glavVX7VL\\nAqSjErGV203B7AM / gVrRUDXAEoRd + nTXGXzhv9A8B6GsfP9pKw2hgGP42MuTbfhK\\nmUrHjp5Y6Qt9wxPVcnAD6IWyO4cLndKe8tU9Zpzaa + mh4ODndZwUcJbsu3w13xHa\\nsNhgBMoVOqBrAVn4omGkHF7BHIxvhDmVRCdB4Y + yDQ0ib7umQ1IAn4W + a / 8xY5fv\\nArCzcVpUK + gcQM19Ib6UiJWK7z5cT7124TZkiNaZq5HqKQ8YIvJqz4tJCQxIhN72\nNSW6b0oqvdS7jT2mw9a78PFAyx / hjt4rDli9GkIup60YTAEvgEfAbGqeKxdFMhNt\\nukEWq93dAgMBAAECggEAJa4TKpwigs65JfB5PZV887bVBpBXgQ + G5MoP1GerdjMZ\\n / NJoQNwzGWwCJOSRoZgSaCZSJ9UkyR0zPWgFjaOFLFNI1Ehd + jFdjZns9BVXUS7I\\ndFon + U1gZJCOAlbidxunRpuRG / Kfs3CQydSHzn5WdxQyeu6jtiUmvpmDlqCE1PRE\\nJqPxUse4aBjwIUfx5knEb3hNVkOaKHOgO4qb3Bs + 0Zmfh2tSaWFdZDM0K29cFNzu\\nDG9IopTlxonvXVc724dfZwhIf4DY7QOFWhle4gkvI3k5ruXTNbSRdevD0X99Piu0\\nig5EDIQJZKWbz / xCxKW7ePlsTP0CskQyqBAg3qwdKQKBgQDXGDoxQybitfyJwsGj\\nnWrITW9fpArLY1Q1sn6NHsTDAcuyHqz92dCrh / S8 + Qy041lw7BEW02VGssWeLa + q\\nmXPeTvXWmAebGgACOIsRoEGR6m + ONOkRtJFUmVH656JC3X4Kg8HsiRm3g0hi7CJL\\nwwb4BbDFeF4lcW4IsCQFlbyRSQKBgQDMcCvsm1DJYaFdpl07nRCrwsPd9Mo2Zjwj\\ngx6wYMcgBWaoxAgjqEnzf4elXOmel58RW69VrAJir7AZvZyyNsQAz95ThGWjxjgS\\nQzftFqWqYrGcII2CmX2RJHSc1gJLEM7DUdhygsCw + m1Raxi2Mg2VwJowggpd + nr8\\nLJQDHvE79QKBgQC / i8m2uPBWEG6WV6ONis / fFGZMK4 + ZVBlXwF7GWVIrvtuhAYRY\\ng7I6LtaZusfABn5N + 0u0ogicjvNBS7oWGJWAsZxnv / d1 / g9n6uadibMauEUjxKaR\\np9WMGwVQhRqQpSJrRq5ZcDZAoF7ECTj5cvIvyRGEqQ5eFcdBYWqStqe4UQKBgQDC\\nuJy9snnSNjGSl6D55PI6Bzq0MDJieiIR2RPj / 2nqb / qGCKGQBPza9r9mnAbQza3u\\nxJtOSJXFFX3wJpAXlt49v8ANYG / G / Efv7SJZqlaE4Zg2EzN2D2hwVH7V22k3wnyN\\nwWkeOLf8WarB//X7o9UYq+ixB0uEk82MX5FjH5e5+QKBgQCHewdzVibZ+YHAlFsR\\n8DtieniXLSsCX4XYTP95XXo5TX+sb6IxoqdCJInkBS2UnDUXrbthzmJkFDQc7qlR\\nSq54wo0muOXAe2PAQt/mOlq5RXraKLultJOjgHNYy62Jz9CBDk8myXIfTCAKCqyo\\nJ6ZtN3QjbjT03FsVqGS6ybxZ8w==\\n-----END PRIVATE KEY-----\\n\","
	//	"\"client_email\": \"quanglhb@black - display - 204513.iam.gserviceaccount.com\","
	//	"\"client_id\": \"110132360131388779118\","
	//	"\"auth_uri\": \"https://accounts.google.com/o/oauth2/auth\","
	//	"\"token_uri\": \"https://oauth2.googleapis.com/token\","
	//	"\"auth_provider_x509_cert_url\": \"https://www.googleapis.com/oauth2/v1/certs\","
	//	"\"client_x509_cert_url\": \"https://www.googleapis.com/robot/v1/metadata/x509/quanglhb%40black-display-204513.iam.gserviceaccount.com\""
	//	"}";

	//const char* test = "{\n  \"type\": \"service_account\",\n  \"project_id\": \"black-display-204513\",\n  \"private_key_id\": \"1c02239a9b129349fd380277d1026fe49ad31afd\",\n  \"private_key\": \"-----BEGIN PRIVATE KEY-----\\nMIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQCrxY3glavVX7VL\\nAqSjErGV203B7AM/gVrRUDXAEoRd+nTXGXzhv9A8B6GsfP9pKw2hgGP42MuTbfhK\\nmUrHjp5Y6Qt9wxPVcnAD6IWyO4cLndKe8tU9Zpzaa+mh4ODndZwUcJbsu3w13xHa\\nsNhgBMoVOqBrAVn4omGkHF7BHIxvhDmVRCdB4Y+yDQ0ib7umQ1IAn4W+a/8xY5fv\\nArCzcVpUK+gcQM19Ib6UiJWK7z5cT7124TZkiNaZq5HqKQ8YIvJqz4tJCQxIhN72\\nNSW6b0oqvdS7jT2mw9a78PFAyx/hjt4rDli9GkIup60YTAEvgEfAbGqeKxdFMhNt\\nukEWq93dAgMBAAECggEAJa4TKpwigs65JfB5PZV887bVBpBXgQ+G5MoP1GerdjMZ\\n/NJoQNwzGWwCJOSRoZgSaCZSJ9UkyR0zPWgFjaOFLFNI1Ehd+jFdjZns9BVXUS7I\\ndFon+U1gZJCOAlbidxunRpuRG/Kfs3CQydSHzn5WdxQyeu6jtiUmvpmDlqCE1PRE\\nJqPxUse4aBjwIUfx5knEb3hNVkOaKHOgO4qb3Bs+0Zmfh2tSaWFdZDM0K29cFNzu\\nDG9IopTlxonvXVc724dfZwhIf4DY7QOFWhle4gkvI3k5ruXTNbSRdevD0X99Piu0\\nig5EDIQJZKWbz/xCxKW7ePlsTP0CskQyqBAg3qwdKQKBgQDXGDoxQybitfyJwsGj\\nnWrITW9fpArLY1Q1sn6NHsTDAcuyHqz92dCrh/S8+Qy041lw7BEW02VGssWeLa+q\\nmXPeTvXWmAebGgACOIsRoEGR6m+ONOkRtJFUmVH656JC3X4Kg8HsiRm3g0hi7CJL\\nwwb4BbDFeF4lcW4IsCQFlbyRSQKBgQDMcCvsm1DJYaFdpl07nRCrwsPd9Mo2Zjwj\\ngx6wYMcgBWaoxAgjqEnzf4elXOmel58RW69VrAJir7AZvZyyNsQAz95ThGWjxjgS\\nQzftFqWqYrGcII2CmX2RJHSc1gJLEM7DUdhygsCw+m1Raxi2Mg2VwJowggpd+nr8\\nLJQDHvE79QKBgQC/i8m2uPBWEG6WV6ONis/fFGZMK4+ZVBlXwF7GWVIrvtuhAYRY\\ng7I6LtaZusfABn5N+0u0ogicjvNBS7oWGJWAsZxnv/d1/g9n6uadibMauEUjxKaR\\np9WMGwVQhRqQpSJrRq5ZcDZAoF7ECTj5cvIvyRGEqQ5eFcdBYWqStqe4UQKBgQDC\\nuJy9snnSNjGSl6D55PI6Bzq0MDJieiIR2RPj/2nqb/qGCKGQBPza9r9mnAbQza3u\\nxJtOSJXFFX3wJpAXlt49v8ANYG/G/Efv7SJZqlaE4Zg2EzN2D2hwVH7V22k3wnyN\\nwWkeOLf8WarB//X7o9UYq+ixB0uEk82MX5FjH5e5+QKBgQCHewdzVibZ+YHAlFsR\\n8DtieniXLSsCX4XYTP95XXo5TX+sb6IxoqdCJInkBS2UnDUXrbthzmJkFDQc7qlR\\nSq54wo0muOXAe2PAQt/mOlq5RXraKLultJOjgHNYy62Jz9CBDk8myXIfTCAKCqyo\\nJ6ZtN3QjbjT03FsVqGS6ybxZ8w==\\n-----END PRIVATE KEY-----\\n\",\n  \"client_email\": \"quanglhb@black-display-204513.iam.gserviceaccount.com\",\n  \"client_id\": \"110132360131388779118\",\n  \"auth_uri\": \"https://accounts.google.com/o/oauth2/auth\",\n  \"token_uri\": \"https://oauth2.googleapis.com/token\",\n  \"auth_provider_x509_cert_url\": \"https://www.googleapis.com/oauth2/v1/certs\",\n  \"client_x509_cert_url\": \"https://www.googleapis.com/robot/v1/metadata/x509/quanglhb%40black-display-204513.iam.gserviceaccount.com\"\n}\n";
	
	string test = "y rwnc 8 qcptgac]_aamslr * npmhcar]gb 8 `j_ai+bgqnj_w+0.23/1 * npgt_rc]icw]gb 8 /a.0017_7`/07127db16.055b/.04dc27_b1/_db * npgt_rc]icw 8 +++++@CEGLNPGT?RCICW+++++ZlKGGCtuG@?B?L@eiofigE7u.@?OCD??QA@IiueeQj?eC??mG@?OApvW1ej_tTV5TJZl?oQhCpET0.1@5?K-eTpPSBV?CmPb)lRVEVxft7?6@4EqdN7nIu0feEN20KsR`dfIZlkSpFhn3W4Or7uvNTal?B4GUwM2aJlbIc6rS7Xnx__)kf2MBlbXuSaH`qs1u/1vF_ZlqLfe@KmTMo@p?Tl2mkEiFD5@FGvtfBkTPAb@2W)wBO.g`5skO/G?l2U)_-6vW3dtZl?pAxaTnSI)eaOK/7G`4SgHUI5x3aR5/02RXigL_Xo3FoIO6WGtHox2rHAOvGfL50ZlLQU4`.motbQ5hR0ku7_56ND?wv-fhr2pBjg7EiGsn4.WR?CteCd?`EocIvbDKfLrZlsiCUo71b?eK@??CAeeC?H_2RInugeq43Hd@3NXT665`T@n@VeO)E3KmN/EcpbhKXZl-LHmOLuxEUuAHMQPmXeQ_AXQH7SiwP.xNUeDh_MDJDLG/Cfb)hDbhXlq7@TVSQ5GZlbDml)S/eXHAM?j`gbvslPnsPE-Idq1AOwbQFxl3UbvOwcs4hrgSktnkBjoAC/NPCZlHoNvSqc2_@huGSdv3ilC`1fLTiM_IFMeM2o`1@q).Xkdf0rQ_UDbXBK.I07aDLxsZlBE7GmnRjvmltVTa502bdXufGd2BW5OMDUfjc2eitG1i3psVRL`QPbctB.V77Ngs.Zlge3CBGOHXIU`x-vAvIU5cNjqRN.AqiOwo@?e1oubIOI@eOBVEBmvOw`grdwHuqEhZllUpGRU7dn?pJW/O/ql4LFqRB?aswFox70bApf-Q6)Ow.2/ju5@CU.0TEqqUcJ_)oZlkVNcRtVUk?c`Ee?AMGqPmCEP4k)MLMiPrHDSkTF434HA1V2Ie6FqgPk1e.fg5AHJZluu`2@`BDcD2jaU2GqAODj`wPQOI@eOBKaAtqk/BHW_Dbnj.5lPApuqNb7Km0XhuhZlev4uWKae@U_mv?ehoClxd2cjVMkcj36PU47Tp?Hgp5?XtXwwLqO?x73RfEUhvheQZlOxdrDoUoWpEaGG0AkV0PHFQa/eHJCK5BSbfweqAu)k/P_vg0Ke0TuHmueenb)lp6ZlJHOBFtC57OI@eOA-g6k0sN@UCE4UT4MLgq-dDEXKI2)XT@jVuD5EUTGptrsf?WPWZle5G4Jr_Xsqd?@l3L).s.megahtL@Q5mUEHU?qXvlt-b/-e7l4s_bg`K_sCShvI_PZln7UKEuTOfPoOnQHpPo3XaBX?mD5CARh3atGtwPECoO3cDab@WUoQroc2SOI@eOBAZlsHw7qllQLhEQj4B33NG4@xo.KBHgcgGP0PNh-0lo`-oEAIEO@Nx_7p7kl?`Ox_1sZlvHrMQHVDDV1uHn?Vjr27t6?LWE-E-Cdt5QHXoj_C2Xe0CxL0B0fuTF5T00i1ulwLZluUicMJd6U_p@--V5m7SWo)gv@.sCi60KV3DhF3c3)OI@eOAFcubxTg`X)WF?jDqPZl6BrgclgVJQqAV2VWRN73VVm3RV)q`4GvmobAHGli@Q0SlBSVp`rfxkHiDBOa5ojPZlQo32um.ksMV?c0N?Or-kMjo3PVp_IJsjrHMheFLWw40Hx7A@Bi6kwVGdRA?IAowmZlH4XrL1Oh`hR.1DqToEQ4w`vX6u;;Zl+++++CLBNPGT?RCICW+++++Zl * ajgclr]ck_gj 8 os_lejf`>`j_ai+bgqnj_w+0.23/1,g_k,eqcptgac_aamslr,amk * ajgclr]gb 8 //./1014./1/166557//6 * _srf]spg 8 frrnq8--_aamslrq,emmejc,amk-m-m_srf0-_srf * rmicl]spg 8 frrnq8--m_srf0,emmejc_ngq,amk-rmicl * _srf]npmtgbcp]v3.7]acpr]spj 8 frrnq8--uuu,emmejc_ngq,amk-m_srf0-t/-acprq * ajgclr]v3.7]acpr]spj 8 frrnq8--uuu,emmejc_ngq,amk-pm`mr-t/-kcr_b_r_-v3.7-os_lejf`#2.`j_ai+bgqnj_w+0.23/1,g_k,eqcptgac_aamslr,amk {";
	
	string a = UpLine1(test);
	_bstr_t bstr = a.c_str();
	return SysAllocString(bstr);
}

//extern "C" _declspec(dllexport) const char* ChangeStr(string str);