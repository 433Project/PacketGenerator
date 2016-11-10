// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_PACKET_FB_H_
#define FLATBUFFERS_GENERATED_PACKET_FB_H_

#include "flatbuffers/flatbuffers.h"

namespace fb {

	struct Body;

	enum Command {
		Command_HEALTH_CHECK = 0,
		Command_NOTI_MATCH_REQUEST = 10,
		Command_NOTI_MATCH_SUCCESS = 11,
		Command_LATENCY = 12,
		Command_MATCH_REQUEST = 13,
		Command_MATCH_RESPONSE = 14,
		Command_MSLIST_REQUEST = 30,
		Command_MSLIST_RESPONSE = 31,
		Command_MS_ID = 32,
		Command_ROOM_CREATE_REQUEST = 40,
		Command_ROOM_CREATE_RESPONSE = 41,
		Command_ROOM_JOIN_REQUEST = 50,
		Command_ROOM_JOIN_RESPONSE = 51,
		Command_GAME_START = 52,
		Command_GAME_END = 53,
		Command_PG_START = 60,
		Command_PG_END = 61,
		Command_PG_DUMMY = 62,
		Command_MIN = Command_HEALTH_CHECK,
		Command_MAX = Command_PG_DUMMY
	};

	inline const char **EnumNamesCommand() {
		static const char *names[] = { "HEALTH_CHECK", "", "", "", "", "", "", "", "", "", "NOTI_MATCH_REQUEST", "NOTI_MATCH_SUCCESS", "LATENCY", "MATCH_REQUEST", "MATCH_RESPONSE", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "MSLIST_REQUEST", "MSLIST_RESPONSE", "MS_ID", "", "", "", "", "", "", "", "ROOM_CREATE_REQUEST", "ROOM_CREATE_RESPONSE", "", "", "", "", "", "", "", "", "ROOM_JOIN_REQUEST", "ROOM_JOIN_RESPONSE", "GAME_START", "GAME_END", "", "", "", "", "", "", "PG_START", "PG_END", "PG_DUMMY", nullptr };
		return names;
	}

	inline const char *EnumNameCommand(Command e) { return EnumNamesCommand()[static_cast<int>(e)]; }

	enum Status {
		Status_SUCCESS = 0,
		Status_FAIL = 1,
		Status_NONE = 2,
		Status_MIN = Status_SUCCESS,
		Status_MAX = Status_NONE
	};

	inline const char **EnumNamesStatus() {
		static const char *names[] = { "SUCCESS", "FAIL", "NONE", nullptr };
		return names;
	}

	inline const char *EnumNameStatus(Status e) { return EnumNamesStatus()[static_cast<int>(e)]; }

	struct Body FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
		enum {
			VT_CMD = 4,
			VT_STATUS = 6,
			VT_DATA = 8
		};
		Command cmd() const { return static_cast<Command>(GetField<int32_t>(VT_CMD, 0)); }
		Status status() const { return static_cast<Status>(GetField<int32_t>(VT_STATUS, 0)); }
		const flatbuffers::String *data() const { return GetPointer<const flatbuffers::String *>(VT_DATA); }
		bool Verify(flatbuffers::Verifier &verifier) const {
			return VerifyTableStart(verifier) &&
				VerifyField<int32_t>(verifier, VT_CMD) &&
				VerifyField<int32_t>(verifier, VT_STATUS) &&
				VerifyField<flatbuffers::uoffset_t>(verifier, VT_DATA) &&
				verifier.Verify(data()) &&
				verifier.EndTable();
		}
	};

	struct BodyBuilder {
		flatbuffers::FlatBufferBuilder &fbb_;
		flatbuffers::uoffset_t start_;
		void add_cmd(Command cmd) { fbb_.AddElement<int32_t>(Body::VT_CMD, static_cast<int32_t>(cmd), 0); }
		void add_status(Status status) { fbb_.AddElement<int32_t>(Body::VT_STATUS, static_cast<int32_t>(status), 0); }
		void add_data(flatbuffers::Offset<flatbuffers::String> data) { fbb_.AddOffset(Body::VT_DATA, data); }
		BodyBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
		BodyBuilder &operator=(const BodyBuilder &);
		flatbuffers::Offset<Body> Finish() {
			auto o = flatbuffers::Offset<Body>(fbb_.EndTable(start_, 3));
			return o;
		}
	};

	inline flatbuffers::Offset<Body> CreateBody(flatbuffers::FlatBufferBuilder &_fbb,
		Command cmd = Command_HEALTH_CHECK,
		Status status = Status_SUCCESS,
		flatbuffers::Offset<flatbuffers::String> data = 0) {
		BodyBuilder builder_(_fbb);
		builder_.add_data(data);
		builder_.add_status(status);
		builder_.add_cmd(cmd);
		return builder_.Finish();
	}

	inline flatbuffers::Offset<Body> CreateBodyDirect(flatbuffers::FlatBufferBuilder &_fbb,
		Command cmd = Command_HEALTH_CHECK,
		Status status = Status_SUCCESS,
		const char *data = nullptr) {
		return CreateBody(_fbb, cmd, status, data ? _fbb.CreateString(data) : 0);
	}

	inline const fb::Body *GetBody(const void *buf) { return flatbuffers::GetRoot<fb::Body>(buf); }

	inline bool VerifyBodyBuffer(flatbuffers::Verifier &verifier) { return verifier.VerifyBuffer<fb::Body>(nullptr); }

	inline void FinishBodyBuffer(flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<fb::Body> root) { fbb.Finish(root); }

}  // namespace fb

#endif  // FLATBUFFERS_GENERATED_PACKET_FB_H_
