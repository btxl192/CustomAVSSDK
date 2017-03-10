/*
 * MessageInterpreter.h
 *
 * Copyright 2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef ALEXA_CLIENT_SDK_ADSL_INCLUDE_ADSL_MESSAGE_INTERPRETER_H_
#define ALEXA_CLIENT_SDK_ADSL_INCLUDE_ADSL_MESSAGE_INTERPRETER_H_

#include <memory>

#include <AVSCommon/ExceptionEncounteredSenderInterface.h>
#include <ACL/AVSConnectionManager.h>
#include <ACL/MessageObserverInterface.h>
#include <ACL/Message.h>
#include <ACL/MessageObserverInterface.h>

#include "ADSL/DirectiveSequencer.h"

namespace alexaClientSDK {
namespace adsl {

/**
 * Class that converts @c acl::Message to @c AVSDirective, and passes those directives to a @c DirectiveSequencer.
 */
class MessageInterpreter : public acl::MessageObserverInterface {
public:
   /**
    * Constructor.
    *
    * @param exceptionEncounteredSender The exceptions encountered messages sender, which will allow us to send
    *        exception encountered back to AVS.
    * @param directiveSequencer The DirectiveSequencerInterface implementation, which will receive @c AVSDirectives.
    */
    MessageInterpreter(std::shared_ptr<avsCommon::ExceptionEncounteredSenderInterface> exceptionEncounteredSender,
        std::shared_ptr<DirectiveSequencer> directiveSequencer);

    void receive(std::shared_ptr<acl::Message> message) override;

private:
    /**
     * This helper function is used to access fields at various levels within the JSON message
     * sent to us from AVS. This function also encapsulates error and exception handling logic appropriately.
     *
     * TODO: [ACSDK-202] Refine this helper function to make sure sending exception encountered event is clear to
     *       the caller.
     *
     * @param aclMessage The message received from ACL.
     * @param jsonMessageHeader The JSON string of message header we are trying to parse, which is a substring of the
     *        directive.
     * @param lookupKey The key we are looking for.
     * @param[out] outputValue The value of the key that we are looking for.
     * @return @c true if the value was found, @false otherwise, in which case an Exception has also been sent to AVS.
     */
    bool lookupJsonValueHelper(std::shared_ptr<acl::Message> aclMessage, const std::string& jsonMessageHeader,
        const std::string& lookupKey, std::string* outputValue);

    /// Object that manages sending exceptions encountered messages to AVS.
    std::shared_ptr<avsCommon::ExceptionEncounteredSenderInterface> m_exceptionEncounteredSender;
    /// Object to which we will send @c AVSDirectives once translated from @c acl::Messages.
    std::shared_ptr<DirectiveSequencer> m_directiveSequencer;
};

} // namespace directiveSequencer
} // namespace alexaClientSDK

#endif //ALEXA_CLIENT_SDK_ADSL_INCLUDE_MESSAGE_INTERPRETER_H_