class Member < ActiveRecord::Base
  # attr_accessible :title, :body
    attr_accessible :title, :body, :number, :name, :full_name, :email, :birthday, :gender, :administrator
end
