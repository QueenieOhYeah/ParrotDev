/**
 * Copyright (C) 2019 Parrot Drones SAS
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in
 *  the documentation and/or other materials provided with the
 *  distribution.
 *  * Neither the name of Parrot nor the names
 *  of its contributors may be used to endorse or promote products
 *  derived from this software without specific prior written
 *  permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 *  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 */

#ifndef MSGHUB_HPP
#define MSGHUB_HPP

#include <stdint.h>

#include <map>
#include <set>
#include <string>
#include <vector>

#include <libpomp.hpp>

#include "msghub_exports.h"

namespace google {
namespace protobuf {
class MessageLite;
} // namespace protobuf
} // namespace google

struct msghub_dump;

namespace msghub {

class Channel;
class MessageHub;

/**
 * Class wrapping a message consisting of a 32-bit Id and a payload.
 * The 32-bit Id is split in 2 fields
 * - high 16-bit: service Id. Used to route messages in the system
 * - low 16-bit: message number. Used to route message in a service
 */
class MSGHUB_API Message {
	POMP_DISABLE_COPY(Message)

public:
	/**
	 * Default constructor, initialize the Id to 0 and an empty payload.
	 */
	Message();

	/**
	 * Constructor.
	 * @param msgId 32-bit Id of the message.
	 * @param data data buffer of the payload.
	 * @param len size of the payload.
	 *
	 * @remarks no copy of the buffer payload is done, the caller shall
	 *          ensure it stays valid when this message is used.
	 */
	Message(uint32_t msgId, const void *data, uint32_t len);

	/**
	 * Destructor. The buffer of the payload is freed only if this object
	 * is the owner of the data (see clone method).
	 */
	~Message();

	/**
	 * Get the Id of the message.
	 * @return 32-bit Id of the message.
	 */
	inline uint32_t getMsgId() const
	{
		return mMsgId;
	}

	/**
	 * Get the service Id of the message.
	 * @return 16-bit service of the message
	 *         (high 16-bit of the message Id).
	 */
	inline uint16_t getServiceId() const
	{
		return static_cast<uint16_t>((mMsgId >> 16) & 0xffff);
	}

	/**
	 * Get the message number of the message.
	 * @return 16-bit message number of the message
	 *         (low 16-bit of the message Id).
	 */
	inline uint16_t getMsgNum() const
	{
		return mMsgId & 0xffff;
	}

	/**
	 * Get the data buffer of the message payload.
	 * @return data buffer of the message payload.
	 */
	inline const void *getData() const
	{
		return mConstData;
	}

	/**
	 * Get the size of the message payload.
	 * @return size of the message payload.
	 */
	inline uint32_t getLen() const
	{
		return mLen;
	}

	/**
	 * Close this message by allocating a new object and copy the internal
	 * payload. The returned message will own the copied payload
	 * @return copy of this message.
	 */
	Message *clone() const;

private:
	/** 32-bit message Id */
	uint32_t mMsgId;

	/** Pointer to the data buffer if the message is not the owner */
	const void *mConstData;

	/** Pointer to the data buffer if the message is the owner */
	void *mData;

	/** Size of the data buffer */
	uint32_t mLen;
};

/**
 * Base class to send messages to peer. The sender shall first be attached to a
 * MessageHub instance to be able to send messages.
 */
class MSGHUB_API MessageSender {
	POMP_DISABLE_COPY(MessageSender)

public:
	/**
	 * Constructor.
	 * @param serviceName service name. Used to get the associated
	 *        service Id.
	 */
	MessageSender(const std::string &serviceName);

	/**
	 * Destructor.
	 */
	virtual ~MessageSender();

	/**
	 * Get the service name.
	 * @return service name.
	 */
	inline const std::string &getServiceName() const
	{
		return mServiceName;
	}

	/**
	 * Send a message.
	 * @param msg message to send.
	 * @param conn remote connection to target. If nullptr, it will
	 *        broadcast the message to all peers connected to the
	 *        associated channel.
	 * @return 0 in case of success, negative errno in case of error.
	 */
	virtual int send(const Message &msg, pomp::Connection *conn = nullptr);

	/**
	 * Send a message.
	 * @param msgNum message number. The full message Id will be computed
	 *        using the service Id itself computed from the service name.
	 * @param data data buffer of the payload.
	 * @param len size of the payload.
	 * @param conn remote connection to target. If nullptr, it will
	 *        broadcast the message to all peers connected to the
	 *        associated channel.
	 * @return 0 in case of success, negative errno in case of error.
	 */
	virtual int send(uint16_t msgNum,
		const void *data,
		uint32_t len,
		pomp::Connection *conn = nullptr);

	/**
	 * Send a message.
	 * @param msgNum message number. The full message Id will be computed
	 *        using the service Id itself computed from the service name.
	 * @param msgLite message to send as a protobuf object. This method will
	 *         serialize the message and send it.
	 * @param conn remote connection to target. If nullptr, and it will
	 *        broadcast the message to all peers connected to the
	 *        associated channel.
	 * @return 0 in case of success, negative errno in case of error.
	 */
	virtual int send(uint16_t msgNum,
		const google::protobuf::MessageLite &msgLite,
		pomp::Connection *conn = nullptr);

	/**
	 * Indicate if one or more peers is connected to this sender
	 * @return true if the sender is attached to a channel which
	 * has has at least one peer
	 * @remarks this can be used to avoid creating useless messages
	 */
	bool hasPeers();

private:
	friend class MessageHub;

private:
	/** Name of the associated service */
	std::string mServiceName;

	/** Id of the associated service (computed from service name during
	 *  attach to a MessageHub instance */
	uint16_t mServiceId;

	/** Associated MessageHub object if attached */
	MessageHub *mMessageHub;

	/** Associated communication channel object if attached */
	Channel *mChannel;
};

/**
 * Base class to receive message from a peer. The handler shall first be
 * attached to a MessageHub instance to be able to receive messages.
 */
class MSGHUB_API MessageHandler {
	POMP_DISABLE_COPY(MessageHandler)

public:
	/**
	 * Constructor.
	 * @param serviceName service name. Used to get the associated
	 *        service Id.
	 */
	MessageHandler(const std::string &serviceName);

	/**
	 * Destructor.
	 */
	virtual ~MessageHandler();

	/**
	 * Get the service name.
	 * @return service name.
	 */
	inline const std::string &getServiceName() const
	{
		return mServiceName;
	}

	/**
	 * Function called to handle/process the message.
	 */
	virtual void handle(const Message &msg) = 0;

private:
	friend class MessageHub;

private:
	/** Name of the associated service */
	std::string mServiceName;

	/** Id of the associated service (computed from service name during
	 *  attach to a MessageHub instance */
	uint16_t mServiceId;
};

/**
 * Central object where all communication channels (servers/clients) are created
 * and all senders/handlers are attached to send/receive messages.
 */
class MSGHUB_API MessageHub {
	POMP_DISABLE_COPY(MessageHub)

public:
	/**
	 * Interface for notification of connection/disconnection of remote
	 * peer for a given connection. It gives the underlying 'pomp'
	 * Connection object to access information about the peer. This
	 * Connection object can also be used to send messages to a given peer
	 * instead of broadcasting them.
	 */
	class ConnectionHandler {
	public:
		/**
		 * Constructor.
		 */
		inline ConnectionHandler() {}

		/**
		 * Destructor.
		 */
		inline virtual ~ConnectionHandler() {}

		/**
		 * Method called when a remote peer is connected.
		 * @param channel associated Channel object.
		 * @param conn associated 'pomp' Connection object.
		 */
		virtual void onConnected(Channel *channel,
			pomp::Connection *conn)
		{
			(void)channel;
			(void)conn;
		}

		/**
		 * Method called when a remote peer is disconnected.
		 * @param channel associated Channel object.
		 * @param conn associated 'pomp' Connection object.
		 */
		virtual void onDisconnected(Channel *channel,
			pomp::Connection *conn)
		{
			(void)channel;
			(void)conn;
		}

		/**
		 * Method called when all channels created in a MessageHub
		 * object have a remote peer connected.
		 */
		virtual void onAllClientsConnected(){};
	};

public:
	/**
	 * Constructor.
	 * @param pompLoop 'pomp' Loop object to use for internal sockets.
	 * @param connectionHandler optional ConnectionHandler object to be
	 *        notified of connections/disconnections of channels.
	 */
	MessageHub(pomp::Loop *pompLoop, ConnectionHandler *connectionHandler);

	/**
	 * Destructor
	 */
	~MessageHub();

	/**
	 * Create and start a server channel.
	 * @param addr address to listen to.
	 * @param mode optional access mode for unix sockets. If not set the
	 *             socket will be created with default access depending on
	 *             the current value of UMASK(2).
	 * @return Channel object that can then be used to attach
	 *         senders/handlers.
	 */
	Channel *startServerChannel(const pomp::Address &addr,
		uint32_t mode = 0);

	/**
	 * Create and start a client channel.
	 * @param addr address to listen to.
	 * @return Channel object that can then be used to attach
	 *         senders/handlers.
	 */
	Channel *startClientChannel(const pomp::Address &addr);

	/**
	 * Stop and destroy all channels.
	 */
	void stop();

	/**
	 * Enable the dump of sent/received messages in logging system.
	 * @param channel if a channel is given only its messages are dumped
	 *        otherwise all messages are dumped.
	 */
	int enableDump(Channel *channel = nullptr);

	/**
	 * Send a message.
	 * @param channel channel on which the message shall be sent.
	 * @param msg message to send.
	 * @param conn remote connection to target. If nullptr, and it will
	 *        broadcast the message to all peers connected to the
	 *        associated channel.
	 * @return 0 in case of success, negative errno in case of error.
	 */
	int sendMessage(Channel *channel,
		const Message &msg,
		pomp::Connection *conn = nullptr);

	/**
	 * Attach a message sender to a channel. All message sent with the given
	 * sender will go through the given channel.
	 * @param msgSender message sender to attach.
	 * @param channel channel to attach.
	 */
	void attachMessageSender(MessageSender *msgSender, Channel *channel);

	/**
	 * Detach a message sender.
	 * @param msgSender message sender to detach.
	 */
	void detachMessageSender(MessageSender *msgSender);

	/**
	 * Attach a message handler. Any message received on any channel with a
	 * service Id matching the one in the handler will be routed.
	 * @param msgHandler message handler to attach.
	 *
	 * @remarks if the given message handler has an empty service name it
	 *          will be attached as a 'generic' handler and will receive all
	 *          messages regarding of their message Id.
	 */
	void attachMessageHandler(MessageHandler *msgHandler);

	/**
	 * Detach a message handler.
	 * @param msgHandler message handler to detach.
	 */
	void detachMessageHandler(MessageHandler *msgHandler);

	/**
	 * During the processing of an incoming message (in any of the 'handle'
	 * method of an attached handler), get the 'pomp' connection object on
	 * which the message was actually received. Can be used to reply only to
	 * this connection.
	 * @return 'pomp' connection object of the current processed message.
	 */
	inline pomp::Connection *getCurrentMessageConnection() const
	{
		return mCurrentMsgConn;
	}

	/**
	 * Send the given message to all sender objects that have a matching
	 * service Id.
	 * @param msg message to send.
	 */
	void forwardMessage(const Message &msg);

	/**
	 * Get the service Id from a service name.
	 * @param name service name.
	 * @return service Id associated with the given service name.
	 */
	uint16_t getServiceId(const std::string &name);

private:
	class PompEventHandler;
	friend class Channel;

private:
	/**
	 * Method called by a channel to notify the reception of a mesage.
	 */
	void recvMessage(Channel *channel,
		pomp::Connection *pompConn,
		const Message &msg);

private:
	/** 'pomp' Loop object */
	pomp::Loop *mPompLoop;

	/** Optional object to notify connections/disconnections */
	ConnectionHandler *mConnectionHandler;

	/** List of all created channels */
	std::vector<Channel *> mChannels;

	/** List of all attached message senders */
	std::map<uint16_t, std::set<MessageSender *>> mMessageSenders;

	/** List of all attached message handlers */
	std::map<uint16_t, std::set<MessageHandler *>> mMessageHandlers;

	/** List of all attached generic message handlers */
	std::set<MessageHandler *> mGenericMessageHandlers;

	/** Store the 'pomp' connection object of the last received message */
	pomp::Connection *mCurrentMsgConn;

	/** Dump object */
	struct msghub_dump *mDump;
};

} /* namespace msghub */

#endif /* !MSGHUB_HPP */
