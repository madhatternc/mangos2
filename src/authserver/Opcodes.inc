/* AUTOGENERATED. DO NOT MODIFY !!! */
/* RULES_MTIME: 1225482740.0 */
case CMSG_LOGON_CHALLENGE:
{
	packet = CMSG_LOGON_CHALLENGE_t::Create (socket);
	if (packet)
	    HandleLogonChallenge (*(CMSG_LOGON_CHALLENGE_t *)packet);
	break;
}
case CMSG_LOGON_PROOF:
{
	packet = CMSG_LOGON_PROOF_t::Create (socket);
	if (packet)
	    HandleLogonProof (*(CMSG_LOGON_PROOF_t *)packet);
	break;
}
case CMSG_RECONNECT_CHALLENGE:
{
	packet = CMSG_RECONNECT_CHALLENGE_t::Create (socket);
	if (packet)
	    HandleReconnectChallenge (*(CMSG_RECONNECT_CHALLENGE_t *)packet);
	break;
}
// Unhandled packet CMSG_RECONNECT_PROOF
case CMSG_REALMLIST:
{
	packet = CMSG_REALMLIST_t::Create (socket);
	if (packet)
	    HandleRealmList (*(CMSG_REALMLIST_t *)packet);
	break;
}
