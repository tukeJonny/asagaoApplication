class Member < ActiveRecord::Base
  # attr_accessible :title, :body
  attr_accessible :title, :body, :number, :name, :full_name, :email, :birthday, :gender, :administrator
  class << self
    def search(query)
      rel = order("number")
      if query.present?
        rel = rel.where("name LIKE ? OR full_name LIKE ?", "%#{query}%", "%#{query}%")
      end
      rel
    end
  end
end
