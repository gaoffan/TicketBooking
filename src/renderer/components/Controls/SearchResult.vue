<template>
<div>
  <div class="topbar block">
  <el-button circle icon="el-icon-back" @click="onBack"></el-button>
     共找到 {{ tableData.length }} 项结果。
     <el-date-picker style="float:right" v-model="buyTicketForm.date" align="right" type="date"></el-date-picker>
  </div>
  <el-table
    :data="tableData"
    border
    style="width: 100%">
    <el-table-column
      fixed
      sortable
      prop="number"
      label="车次"
      width="80">
    </el-table-column>
    <el-table-column
      prop="departure"
      label="出发站"
      width="90"
      :filters="departureFilters"
      :filter-method="filterHandler">
    </el-table-column>
    <el-table-column
      prop="arrival"
      label="到达站"
      width="90"
      :filters="arrivalFilters"
      :filter-method="filterHandler">
    </el-table-column>
    <el-table-column
      sortable
      prop="departureTime"
      label="出发时间"
      width="120">
    </el-table-column>
    <el-table-column
      sortable
      prop="arrivalTime"
      label="到达时间"
      width="120">
    </el-table-column>
    <el-table-column
      sortable
      prop="cost"
      label="历时"
      width="90">
    </el-table-column>
    <el-table-column
      prop="businessClass"
      label="商务座"
      width="90">
    </el-table-column>
    <el-table-column
      prop="firstClass"
      label="一等座"
      width="90">
    </el-table-column>
    <el-table-column
      prop="secondClass"
      label="二等座"
      width="90">
    </el-table-column>
    <el-table-column
      fixed="right"
      label="操作"
      width="100">
      <template slot-scope="scope">
        <el-button type="primary" size="mini" @click="onSubmit(scope.$index)">预定</el-button>
      </template>
    </el-table-column>
  </el-table>
  <el-dialog title="预定车票" :visible.sync="dialogFormVisible" width="600px">
    <div style="text-align:center">
    <h1>{{buyTicketForm.number}} {{buyTicketForm.departure}} -- {{buyTicketForm.arrival}} {{buyTicketForm.departureTime}} 
      <red>        ¥{{buyTicketForm.price}} / 张</red></h1>
    </div>
    <el-form :model="buyTicketForm" label-width="80px"> 
    <el-form-item label="席位等级">
    <el-radio v-model="buyTicketForm.seatClass" label="3" border size="medium">商务座</el-radio>
    <el-radio v-model="buyTicketForm.seatClass" label="2" border size="medium">一等座</el-radio>
    <el-radio v-model="buyTicketForm.seatClass" label="1" border size="medium">二等座</el-radio>
    </el-form-item>
    <el-form-item label="购买数量">
      <el-input-number size="small" v-model="buyTicketForm.count" :min="1" :max="5"></el-input-number>
    </el-form-item>
    <el-form-item v-for="(i, index) in buyTicketForm.seat" :key="index" :label="'选座' + (index + 1)">
    <el-cascader expand-trigger="hover" :options="options" v-model="i.value" @change="handleChange"></el-cascader>
    </el-form-item>
    </el-form>    
  <span slot="footer" class="dialog-footer">
    <red>共需支付: ¥{{buyTicketForm.totalprice}}</red>
  <el-button type="primary" @click="onBuy(dialogData)">确定</el-button>
  <el-button @click="dialogFormVisible = false">取消</el-button>
  </span>
</el-dialog>
</div>
</template>


<script>
  export default {
    name: 'SearchResult',
    methods: {
      onBack () {
        this.$emit('onback')
      },
      onSubmit (i) {
        this.buyTicketForm.number = this.tableData[i].number
        this.buyTicketForm.departure = this.tableData[i].departure
        this.buyTicketForm.arrival = this.tableData[i].arrival
        this.buyTicketForm.departureTime = this.tableData[i].departureTime
        this.buyTicketForm.baseprice = this.tableData[i].price
        this.dialogFormVisible = true
      },
      onBuy (i) {
        this.$emit('onbuy', this.buyTicketForm)
      },
      deleteRow (index, rows) {
        rows.splice(index, 1)
      },
      resetDateFilter () {
        this.$refs.filterTable.clearFilter('date')
      },
      clearFilter () {
        this.$refs.filterTable.clearFilter()
      },
      formatter (row, column) {
        return row.address
      },
      filterTag (value, row) {
        return row.tag === value
      },
      filterHandler (value, row, column) {
        const property = column['property']
        return row[property] === value
      },
      handleChange (value) {
        console.log(value)
      }
    },
    created () {
      console.log(this.$parent.form.departureDate)
      this.buyTicketForm.date = this.$parent.form.departureDate
      for (let i = 1; i < 60; i++) {
        this.options.push({value: i, label: i, children: [{value: 'A', label: 'A(靠窗)'}, {value: 'B', label: 'B'}, {value: 'C', label: 'C'}, {value: 'E', label: 'E'}, {value: 'F', label: 'F(靠窗)'}]})
      }
      console.log(this.options)
    },
    data () {
      return {
        dialogFormVisible: false,
        buyTicketForm: {
          date: '1999-01-01',
          number: '',
          departure: '',
          departureTime: '',
          arrival: '',
          seatClass: '1',
          baseprice: '',
          price: '',
          count: 1,
          seat: [{value: []}],
          totalprice: ''
        },
        options: [],
        selectedOptions: [],
        tableData: [],
        departureFilters: [],
        arrivalFilters: []
      }
    },
    computed: {
      basePriceChange () {
        return this.buyTicketForm.baseprice
      },
      classChange () {
        return this.buyTicketForm.seatClass
      },
      countChange () {
        return this.buyTicketForm.count
      }
    },
    watch: {
      basePriceChange (val) {
        this.buyTicketForm.totalprice = this.buyTicketForm.price = this.buyTicketForm.baseprice
      },
      classChange (val) {
        this.buyTicketForm.price = parseInt(this.buyTicketForm.baseprice) * parseInt(this.buyTicketForm.seatClass)
        this.buyTicketForm.totalprice = parseInt(this.buyTicketForm.price) * parseInt(this.buyTicketForm.count)
      },
      countChange (val) {
        if (this.buyTicketForm.seat.length > val) {
          this.buyTicketForm.seat.splice(this.buyTicketForm.seat.length - 1, 1)
        }
        if (this.buyTicketForm.seat.length < val) {
          this.buyTicketForm.seat.push({value: []})
        }
        this.buyTicketForm.totalprice = parseInt(this.buyTicketForm.price) * parseInt(this.buyTicketForm.count)
      }
    }
  }
</script>

<style>
.topbar {
  color: #303133;
  margin-bottom: 1rem;
  margin-right: 1rem;
}
red{
  color:red;
}
</style>
