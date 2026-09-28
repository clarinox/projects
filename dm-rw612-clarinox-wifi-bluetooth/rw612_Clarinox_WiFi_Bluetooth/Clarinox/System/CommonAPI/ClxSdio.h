#ifndef CLX_SDIO_h
#define CLX_SDIO_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxSdio.h
* Description         Declares a generic SDIO interface
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#ifdef __cplusplus

class SdioModule;


namespace ClarinoxIO
{
    
    class Sdio 
#if defined(CLX_DEBUG)
    : public Clarinox::WifiHciDebugMessageGenerator
#endif
    {
	private:
		friend class SdioModule;

	private:
		ClxSdio			handle_;

    private:
	    Sdio(ClxSdio handle);
		~Sdio();

    private:
	    ClxResult			sendRequest(ClxSdioRequest& request, 
										u4 sdioProtocolID = 0);
	    
    public:
        static ClarinoxIO::Sdio* open (const s1* name);
        static void close(ClarinoxIO::Sdio& obj);

    public:
        ClxResult enableFunction (ClxSdioFunction function, ClxSdioIrqHandler irqHandler, void* irqHandlerUserData)
        {
        	return clxSdioBspInterface->enableFunction(handle_, function, irqHandler, irqHandlerUserData);
        }
             
        ClxResult disableFunction (ClxSdioFunction function)
        {
        	return clxSdioBspInterface->disableFunction(handle_, function);     	
        }
        
        void lockInterruptContext ()
        {
        	clxSdioBspInterface->lockInterruptContext(handle_);
        }
             
        void unlockInterruptContext ()
        {
        	clxSdioBspInterface->unlockInterruptContext(handle_);     	
        }
        
        ClxSdioDataBufferHandle allocDataBuffer (size_t size, void** addr)
        {
            return clxSdioBspInterface->allocDataBuffer(size, addr);
        }

        void freeDataBuffer (ClxSdioDataBufferHandle handle)
        {
        	clxSdioBspInterface->freeDataBuffer(handle);
        }
        
		ClxResult getFunctionBlockSize(ClxSdioFunction function, u2& blockSize)
		{
			ClxSdioRequest request;
			
			request.type = ClxSdio_GetFunctionBlockSize;
			request.function = function;
			request.data = (u1*)&blockSize;
			request.length = 2;
			request.bufferHandle = NULL;
			/* The rest of request parameters will be ignored: */
			return clxSdioBspInterface->sendRequest(handle_, &request);	
		}

		ClxResult setFunctionBlockSize(ClxSdioFunction function, const u2& blockSize)
		{
			ClxSdioRequest request;
			
			request.type = ClxSdio_SetFunctionBlockSize;
			request.function = function;
			request.data = (u1*)const_cast<u2*>(&blockSize);
			request.length = 2;
			request.bufferHandle = NULL;
			/* The rest of request parameters will be ignored: */
			return clxSdioBspInterface->sendRequest(handle_, &request);	
		}
		
		ClxResult enableFunctionInterrupt(ClxSdioFunction function)
		{
			ClxSdioRequest request;
			request.type = ClxSdio_EnableFunctionInterrupt;
			request.function = function;
			/* The rest of request parameters will be ignored: */
			return clxSdioBspInterface->sendRequest(handle_, &request);
		}

		ClxResult disableFunctionInterrupt(ClxSdioFunction function)
		{
			ClxSdioRequest request;
			request.type = ClxSdio_DisableFunctionInterrupt;
			request.function = function;
			/* The rest of request parameters will be ignored: */
			return clxSdioBspInterface->sendRequest(handle_, &request);
		}	
		
	    ClxResult writeRegister(ClxSdioFunction function, 
		    ClxSdioRegAddr registerAddress, 
		    const u1& value,
			u4 sdioProtocolID = 0)
        {
	    	ClxSdioRequest request;
	    	
            request.type = ClxSdio_WriteRegister;
            request.function = function;
            request.data = const_cast<u1*>(&value);
            request.length = 1;
            request.registerAddress = registerAddress;
            request.bufferHandle = NULL;
            return sendRequest(request, sdioProtocolID);
        }

	    ClxResult readRegister(ClxSdioFunction function, 
		    ClxSdioRegAddr registerAddress, 
		    u1& value,
			u4 sdioProtocolID = 0)
        {
	    	ClxSdioRequest request;
	    	
            request.type = ClxSdio_ReadRegister;
            request.function = function;
            request.data = &value;
            request.length = 1;
            request.registerAddress = registerAddress;
            request.bufferHandle = NULL;
            return sendRequest(request, sdioProtocolID);
        }

	    ClxResult writeDataBuf(ClxSdioFunction function, 
		    ClxSdioRegAddr startAddress, 
		    boolean incrementalAddr, 
		    const u1* data, 
		    u2 dataLen,
		    ClxSdioDataBufferHandle bufferHandle,
			u4 sdioProtocolID = 0)
        {
	    	ClxSdioRequest request;
	    	
            request.type = incrementalAddr ? ClxSdio_WriteDataBuffer_IncAddr : ClxSdio_WriteDataBuffer_FixedAddr;
            request.function = function;
            request.data = (u1*)data;
            request.length = dataLen;
            request.registerAddress = startAddress;
            request.bufferHandle = bufferHandle;
            return sendRequest(request, sdioProtocolID);
        }

	    ClxResult readDataBuf(ClxSdioFunction function, 
		    ClxSdioRegAddr startAddress, 
		    boolean incrementalAddr, 
		    u1* buf, 
		    u2 bufLen,
		    ClxSdioDataBufferHandle bufferHandle,
			u4 sdioProtocolID = 0)
        {
	    	ClxSdioRequest request;
	    	
            request.type = incrementalAddr ? ClxSdio_ReadDataBuffer_IncAddr : ClxSdio_ReadDataBuffer_FixedAddr;
            request.function = function;
            request.data = buf;
            request.length = bufLen;
            request.registerAddress = startAddress;
            request.bufferHandle = bufferHandle;
            return sendRequest(request, sdioProtocolID);
        }

	    ClxResult writeDataBlocks(ClxSdioFunction function, 
		    ClxSdioRegAddr startAddress, 
		    boolean incrementalAddr, 
		    const u1* data, 
		    u2 dataLen,
		    ClxSdioDataBufferHandle bufferHandle,
			u4 sdioProtocolID = 0)
        {
	    	ClxSdioRequest request;
	    	
            request.type = incrementalAddr ? ClxSdio_WriteDataBlocks_IncAddr : ClxSdio_WriteDataBlocks_FixedAddr;
            request.function = function;
            request.data = (u1*)data;
            request.length = dataLen;
            request.registerAddress = startAddress;
            request.bufferHandle = bufferHandle;
            return sendRequest(request, sdioProtocolID);
        }

	    ClxResult readDataBlocks(ClxSdioFunction function, 
		    ClxSdioRegAddr startAddress, 
		    boolean incrementalAddr, 
		    u1* buf, 
		    u2 dataLen,
		    ClxSdioDataBufferHandle bufferHandle,
			u4 sdioProtocolID = 0)
        {
	    	ClxSdioRequest request;
	    	
            request.type = incrementalAddr ? ClxSdio_ReadDataBlocks_IncAddr : ClxSdio_ReadDataBlocks_FixedAddr;
            request.function = function;
            request.data = (u1*)buf;
            request.length = dataLen;
            request.registerAddress = startAddress;
            request.bufferHandle = bufferHandle;
            return sendRequest(request, sdioProtocolID);
        }

	    ClxSdio handle()
	    {
	    	return handle_;
	    }
    };
	
}
#endif // #ifdef __cplusplus


#ifdef __cplusplus
extern "C" {
#endif

extern ClxSdio clxOpenSdioHandle (const s1* name);
extern void clxCloseSdioHandle (ClxSdio handle);

#ifdef __cplusplus
}
#endif



#endif // CLX_SDIO_h
