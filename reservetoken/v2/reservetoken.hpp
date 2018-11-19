#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

#include <string>

namespace eosiosystem
{
class system_contract;
}

namespace eosio
{
using std::string;

CONTRACT reservetoken : public contract
{
  public:
    using contract::contract;

    ACTION create(name issuer, asset maximum_supply);

    ACTION issue(name to, asset quantity, string memo);

    ACTION burn(asset quantity);

    ACTION transfer(name from, name to, asset quantity, string memo);

    ACTION setmaxsupply(asset maximum_supply);

    inline asset get_supply(symbol_code sym) const;

    inline asset get_max_supply(symbol_code sym) const;

    inline asset get_balance(name owner, symbol_code sym) const;

  private:
    TABLE account
    {
        asset balance;

        uint64_t primary_key() const { return balance.symbol.code().raw(); }
    };

    TABLE currency_stats
    {
        asset supply;
        asset max_supply;
        name issuer;

        uint64_t primary_key() const { return supply.symbol.code().raw(); }
    };

    typedef eosio::multi_index<"accounts"_n, account> accounts;
    typedef eosio::multi_index<"stat"_n, currency_stats> stats;

    void sub_balance(name owner, asset value);
    void add_balance(name owner, asset value, name ram_payer);

  public:
    struct transfer_args
    {
        name from;
        name to;
        asset quantity;
        string memo;
    };
};

asset reservetoken::get_supply(symbol_code sym) const
{
    stats statstable(_self, sym);
    const auto &st = statstable.get(sym);
    return st.supply;
}

asset reservetoken::get_max_supply(symbol_code sym) const
{
    stats statstable(_self, sym);
    const auto &st = statstable.get(sym);
    return st.max_supply;
}

asset reservetoken::get_balance(name owner, symbol_code sym) const
{
    accounts accountstable(_self, owner);
    const auto &ac = accountstable.get(sym);
    return ac.balance;
}

} // namespace eosio