#coding: utf-8
require 'test_helper'


class MemberTest < ActiveSupport::TestCase
   test "the truth" do
     assert true
   end

  test "factory girl" do
    member = Factory(:member)
    assert_equal "Yamada Taro", member.full_name
  end
end
