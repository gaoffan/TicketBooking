<template>
<div>
  <div class="topbar block">
  <el-button circle icon="el-icon-back" @click="onBack"></el-button>
     共找到 {{ tableData.length }} 项结果。
     <el-date-picker style="float:right" v-model="buyTicketForm.date" align="right" type="date" value-format="yyyy-MM-dd"></el-date-picker>
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
        <el-button type="primary" size="mini" @click="onSubmit(scope.$index)">预订</el-button>
      </template>
    </el-table-column>
  </el-table>
  <el-dialog title="预订车票" v-if="dialogFormVisible" :visible.sync="dialogFormVisible" width="600px">
    <div style="text-align:center">
    <h1>{{buyTicketForm.number}} {{buyTicketForm.departure}} -> {{buyTicketForm.arrival}} {{buyTicketForm.departureTime}} 
      <red>        ¥{{buyTicketForm.price}}/张</red></h1>
    </div>
    <el-form :model="buyTicketForm" label-width="80px"> 
    <el-form-item label="席位等级" required prop="seatClass">
    <el-radio v-model="buyTicketForm.seatClass" :disabled="tableData[index].businessClass === 0" 
    label="3" border size="medium" @change="onClassChange">商务座</el-radio>
    <el-radio v-model="buyTicketForm.seatClass" :disabled="tableData[index].firstClass === 0" 
    label="2" border size="medium" @change="onClassChange">一等座</el-radio>
    <el-radio v-model="buyTicketForm.seatClass" :disabled="tableData[index].secondClass === 0" 
    label="1" border size="medium" @change="onClassChange">二等座</el-radio>
    </el-form-item>
    <el-form-item label="购买数量" required prop="count">
      <el-input-number size="small" v-model="buyTicketForm.count" :min="1" :max="5"></el-input-number>
    </el-form-item>
    <el-form-item required prop="seat" v-for="(i, index) in buyTicketForm.seat" :key="index" :label="'选座' + (index + 1)">
    <el-cascader expand-trigger="hover" :options="options" v-model="i.value"></el-cascader>
    </el-form-item>
    </el-form>    
  <span slot="footer" class="dialog-footer">
    <red>共需支付: ¥{{buyTicketForm.totalprice}}</red>
  <el-button style="margin-left: 1rem" type="primary" @click="onBuy()">确定</el-button>
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
      onClassChange (cls) {
        this.options = []
        if (cls === '3') {
          for (let j = 1; j < 4; j++) {
            let child = {
              value: j,
              label: j + '车',
              children: []
            }
            this.options.push(child)
            for (let i = 1; i < 10; i++) {
              child.children.push({
                value: i,
                label: i + '列',
                children: [
                  {value: 'A', label: 'A'}, {value: 'F', label: 'F'}
                ]
              })
            }
          }
        } else if (cls === '2') {
          for (let j = 4; j < 10; j++) {
            let child = {
              value: j,
              label: j + '车',
              children: []
            }
            this.options.push(child)
            for (let i = 1; i < 20; i++) {
              child.children.push({
                value: i,
                label: i + '列',
                children: [
                  {value: 'A', label: 'A(靠窗)'}, {value: 'B', label: 'B'}, {value: 'E', label: 'E'}, {value: 'F', label: 'F(靠窗)'}
                ]
              })
            }
          }
        } else {
          for (let j = 10; j < 17; j++) {
            let child = {
              value: j,
              label: j + '车',
              children: []
            }
            this.options.push(child)
            for (let i = 1; i < 60; i++) {
              child.children.push({
                value: i,
                label: i + '列',
                children: [
                  {value: 'A', label: 'A(靠窗)'}, {value: 'B', label: 'B'}, {value: 'C', label: 'C'}, {value: 'E', label: 'E'}, {value: 'F', label: 'F(靠窗)'}
                ]
              })
            }
          }
        }
      },
      onSubmit (i) {
        this.index = i
        this.buyTicketForm.number = this.tableData[i].number
        this.buyTicketForm.departure = this.tableData[i].departure
        this.buyTicketForm.arrival = this.tableData[i].arrival
        this.buyTicketForm.departureTime = this.tableData[i].departureTime
        this.buyTicketForm.baseprice = this.tableData[i].price
        this.dialogFormVisible = true
      },
      onBuy () { // yyc
        if (!this.buyTicketForm.seatClass) {
          this.$message({message: '请选择席位等级！', type: 'warning'})
          return
        }
        // console.log(this.buyTicketForm.seat)
        let seat = [] // 进行预处理
        for (let i of this.buyTicketForm.seat) {
          if (i.value.length === 0) {
            this.$message({message: '请选择座位！', type: 'warning'})
            return
          } else {
            if (seat.includes(i.value[0] + i.value[1] + i.value[2])) {
              this.$message({message: '座位不能相同！', type: 'warning'})
              return
            }
            seat.push(i.value[0] + i.value[1] + i.value[2])
          }
        }
        if (this.buyTicketForm.seatClass === '3') {
          let x = parseInt(this.tableData[this.index].businessClass) - parseInt(this.buyTicketForm.count)
          if (x > -1) {
            this.tableData[this.index].businessClass = x
          } else {
            this.$message({message: '超过了可预订的票数！', type: 'warning'})
            return
          }
        } else if (this.buyTicketForm.seatClass === '2') {
          let x = parseInt(this.tableData[this.index].firstClass) - parseInt(this.buyTicketForm.count)
          if (x > -1) {
            this.tableData[this.index].firstClass = x
          } else {
            this.$message({message: '超过了可预订的票数！', type: 'warning'})
            return
          }
        } else if (this.buyTicketForm.seatClass === '1') {
          let x = parseInt(this.tableData[this.index].secondClass) - parseInt(this.buyTicketForm.count)
          if (x > -1) {
            this.tableData[this.index].secondClass = x
          } else {
            this.$message({message: '超过了可预订的票数！', type: 'warning'})
            return
          }
        }
        // console.log(seat)
        this.$emit('onbuy', this.buyTicketForm) // 买票
        this.dialogFormVisible = false
      },
      filterHandler (value, row, column) {
        const property = column['property']
        return row[property] === value
      }
    },
    created () {
      // console.log(this.$parent.form.departureDate)
      this.buyTicketForm.date = this.$parent.form.departureDate
      // console.log(this.options)
    },
    data () {
      return {
        index: 0,
        dialogFormVisible: false,
        buyTicketForm: {
          date: '',
          number: '',
          departure: '',
          departureTime: '',
          arrival: '',
          seatClass: '',
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
