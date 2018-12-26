#pragma once

#include <streambuf>
#include <sstream>
#include "MailBox.h"

namespace DrawProject {

	class WPFConsoleStream : public std::streambuf {
	private:
		Kernel::MailBox* mailBox;
		std::string buffer;
	protected:

		virtual int overflow(int c) override {
			if (c == traits_type::eof()) {
				return traits_type::eof();
			}

			char_type ch = static_cast<char_type>(c);

			if (ch == '\n') {
				auto mess = new Kernel::Message();
				mess->code = Kernel::logging;
				mess->strArr = CreateArr(buffer);

				mailBox->SendMessage(mess);

				buffer = "";
				return ch;
			}

			buffer += ch;

			return ch;
		}

	public:
		WPFConsoleStream(Kernel::MailBox* _mailBox) : mailBox(_mailBox) { }
	};

}