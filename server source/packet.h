Search:
	HEADER_CG_MYSHOP = 55,

Add in under:
	HEADER_CG_SHOP2 = 56,

---

Search:
typedef struct command_shop
{
	BYTE	header;
	BYTE	subheader;
} TPacketCGShop;

Add in under:
enum
{
	SHOP2_SUBHEADER_EMPTY,
	SHOP2_SUBHEADER_CG_BUY,
	SHOP2_SUBHEADER_CG_SEARCH
};

enum
{
	SHOP2_SEARCHER_TYPE_EMPTY,
	SHOP2_SEARCHER_TYPE_FIND,
	SHOP2_SEARCHER_TYPE_BUY,
	SHOP2_SEARCHER_TYPE_BUY_PREMIUM
};


typedef struct command_shop2
{
	BYTE        header; // Common Request +
	BYTE		subheader; // Common Request -

	char		cSellerName[24 + 1]; // Buy Request +
	BYTE		bItemPos;
	int			iBuyType; // Buy Request -

	int			iJob; // Search Request +
	int			iType;
	int			iSubtype;
	int			iMinLevel;
	int			iMaxLevel;
	int			iMinRefine;
	int			iMaxRefine;
	int			iMinPrice;
	int			iMaxPrice;
	char		cItemNameForSearch[24 + 1]; // Search Request +
} TPacketCGShop2;
