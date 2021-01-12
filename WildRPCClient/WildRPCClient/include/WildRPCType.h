#pragma once

#if defined(WRPC_DYNAMIC_EXPORT)
#define WRPC_DLLEXPORT __declspec(dllexport)
#elif defined(WRPC_DYNAMIC_IMPORT)
#define WRPC_DLLEXPORT __declspec(dllimport)
#else
#define WRPC_DLLEXPORT
#endif

namespace WRPC
{
    static const char* RPC_PROTOCOL_ERROR_STRINGS[12] = {
        "No Error",
        "Exceeded BufferSize",
        "Header Missing",
        "Manager Class Not Found",
        "Manager Method Not Found",
        "Manager Method Not Valid",
        "Types Mismatch",
        "Send Buffer Too Small",
        "Wrong Port",
        "No Connection To Host",
        "Wrong Reply Buffer Size",
        "ExceededReplyBufferSize"};

    enum class RPCProtocolError
    {
        No_Error = 0,
        Exceeded_BufferSize,
        HeaderMissing,
        ManagerClassNotFound,
        ManagerMethodNotFound,
        ManagerMethodNotValid,
        TypesMismatch,
        SendBufferTooSmall,
        WrongPort,
        NoConnectionToHost,
        WrongReplyBufferSize,
        Exceeded_ReplyBufferSize
    };

    enum class ConnectionStatus
    {
        NotConnected = 0,
        Connected,
        Errored,
        COUNT
    };

    struct RPC_Error
    {
        RPCProtocolError m_protocolError = RPCProtocolError::No_Error;
        unsigned char m_applicativeError = 0;
    };

} // namespace WRPC
