Search:
PyObject* netSendShopBuyPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iCount;
	if (!PyTuple_GetInteger(poArgs, 0, &iCount))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendShopBuyPacket(iCount);
	return Py_BuildNone();
}

Add it under:
PyObject* netSendShopSearchBuyPacket(PyObject* poSelf, PyObject* poArgs)
{
	char * pcSellerName;
	if (!PyTuple_GetString(poArgs, 0, &pcSellerName))
		return Py_BuildException();
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 1, &iPos))
		return Py_BuildException();
	int iBuyType;
	if (!PyTuple_GetInteger(poArgs, 2, &iBuyType))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendShopSearchBuyPacket(pcSellerName, iPos, iBuyType);
	return Py_BuildNone();
}

PyObject* netSendShopSearchFindPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iJob;
	if (!PyTuple_GetInteger(poArgs, 0, &iJob))
		return Py_BuildException();
	int iType;
	if (!PyTuple_GetInteger(poArgs, 1, &iType))
		return Py_BuildException();
	int iSubType;
	if (!PyTuple_GetInteger(poArgs, 2, &iSubType))
		return Py_BuildException();
	int iMinLevel;
	if (!PyTuple_GetInteger(poArgs, 3, &iMinLevel))
		return Py_BuildException();
	int iMaxLevel;
	if (!PyTuple_GetInteger(poArgs, 4, &iMaxLevel))
		return Py_BuildException();
	int iMinRefine;
	if (!PyTuple_GetInteger(poArgs, 5, &iMinRefine))
		return Py_BuildException();
	int iMaxRefine;
	if (!PyTuple_GetInteger(poArgs, 6, &iMaxRefine))
		return Py_BuildException();
	int iMinPrice;
	if (!PyTuple_GetInteger(poArgs, 7, &iMinPrice))
		return Py_BuildException();
	int iMaxPrice;
	if (!PyTuple_GetInteger(poArgs, 8, &iMaxPrice))
		return Py_BuildException();
	char * pcItemName;
	if (!PyTuple_GetString(poArgs, 9, &pcItemName))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendShopSearchFindPacket(iJob, iType, iSubType, iMinLevel, iMaxLevel, iMinRefine, iMaxRefine, iMinPrice, iMaxPrice, pcItemName);

	return Py_BuildNone();
}

---

Search:
		{ "SendShopBuyPacket",					netSendShopBuyPacket,					METH_VARARGS },

Add it under:
		{ "SendShopSearchBuyPacket",			netSendShopSearchBuyPacket,				METH_VARARGS },
		{ "SendShopSearchFindPacket",			netSendShopSearchFindPacket,			METH_VARARGS },
